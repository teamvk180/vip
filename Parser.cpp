/**
  * File: Parser.cpp
  * Description: Implementation file for Parser.
  */

#include "Parser.h"
#include "ast.h"
#include "Lexer.h"
#include "Token.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
using std::cout;
using std::endl;
//#define DEBUG 1
const std::string isSpace = "\t";

//tools for parsing
Parser::Parser(vector<string> file_s)
{
    HasError = false;
    for (const auto d : file_s)
    {
        lex.openFile(d);

        next();
        try
        {
            while (!match(type::EOS))
            {

                Expression *stmt = this->statements();
                if (stmt != nullptr)
                {
                    ast_node.push_back(stmt);
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        lex.closeFile();
    }
}

bool Parser::eval(type tokenType, const std::string errorMssg)
{
    if (match(tokenType))
    {
        next();
        return true;
    }
    else
    {
        Error(errorMssg);
        return false;
    }
}

bool Parser::eval(std::string token_type, const std::string errorMessage)
{
    if (match(token_type))
    {
        next();
        return true;
    }
    else
    {
        Error(errorMessage);
        return false;
    }
}
bool Parser::match(type p1)
{
    if (currentToken.token_type == p1)
    {
        return true;
    }

    return false;
}
bool Parser::match(std::string p1)
{

    if (currentToken.lexeme == p1)
    {
        return true;
    }
    return false;
}
void Parser::Error(const std::string &errorMssg)
{
    std::cout << errorMssg << std::endl;
    std::cout << "Error line: " << currentToken.current_line << " column: " << std::endl;
    throw ParseException("Parse Exception");
}


Expression *Parser::parseParenExpr()
{
    if (match(type::LPAR))
    {
        next();
    }
    Expression *my_t = new Expression();
    while (!match(type::LBRACE) || !match(type::SEMICOLON))
    {
        Expression *t = this->expr();
        if (t != nullptr)
        {
         my_t->expr.push_back(t);
        }
        else
        {
            next();
        }
    }

    eval(type::RPAR, "expected ')'");
    return my_t;
}

Expression *Parser::parseBlock()
{
#ifdef DEBUG
    cout << "block detected " << (int)currentToken.token_type << endl;
#endif
    Expression *b = new Expression();
    eval(type::LBRACE, "Expected '{'");
    while (!match(type::RBRACE))
    {
        if (match(type::EOS))
        {
            break;
        }
        Expression *k = this->statements();
        if (k != nullptr)
        {
            b->expr.push_back(k);
        }
    }
    eval(type::RBRACE, "Expected '}'");
    return b;
}

Expression *Parser::parseWhileExpr()
{
    //eat while
    eval(type::WHILE, "while expected ");
    Expression *condition = this->expr();
    Expression *body = this->parseBlock();
    Expression *while_node = new Expression();
    while_node->node=node_type::WHILE_NODE;
    while_node->expr.push_back(condition);
    while_node->expr.push_back(body);
    return while_node;
}

Expression *Parser::ClassDecl()
{
#ifdef DEBUG
    cout << "class detected " << endl;
#endif
    Expression *p = new Expression();
    eval(type::CLASS, "expected 'class'");
    p->token = currentToken;
    eval(type::IDENTIFIER, "expected class name");
    if(match(type::ASSIGN))
    {
       next();
         eval("depends","expected depends");
       eval(type::IDENTIFIER,"expected dependency name");
       if(match(type::SEMICOLON))
       {
           next();
       }
    }
    p->expr.push_back(this->parseBlock());
    return p;
}
Expression *Parser::parseClassInstance(std::string cls_name)
{
#ifdef DEBUG
    std::cout << currentToken.lexeme << " >> type : " << (int)currentToken.token_type << "\tparseClassInstance" << std::endl;
#endif
    //eat let
    Expression *var = new Expression();
    var->data = cls_name;
    if (match(type::LESS_THAN))
    {
        next();
        while (!match(type ::GREATER_THAN))
        {
            if (match(type::SEMICOLON) || match(type::ASSIGN))
            {
                Error("invalid token " + currentToken.lexeme);
                break;
            }
            else if (match(type::COMMA))
            {
                next();
            }
            else if (match(type::IDENTIFIER))
            {
               // var->i.push_back(currentToken.lexeme);
                eval(type::IDENTIFIER, "expected variable name ");
            }
            else
            {
                Error("only identifier is allowed but got l " + currentToken.lexeme);
            }
        }
        eval(type::GREATER_THAN, "expected > symbol ");
        var->token = currentToken;
        eval(type::IDENTIFIER, "expected an instance name got " + currentToken.lexeme);
        if (match(type::ASSIGN))
        {
            next();
            var->expr.push_back(this->expr());
            return var;
        }

        return var;
    }
    else if (match(type::ASSIGN))
    {
        Error("unexpected assignment at var-decl '" + currentToken.lexeme + "'");
    }
    else if (match(type::IDENTIFIER))
    {
        //var->cls_assign = this->parseInstanceAssign();
        return var;
    }
    else
    {
        Error("unknown token at var-decl '" + currentToken.lexeme + "'");
    }

    return var;
}
Expression *Parser::parseInstanceAssign()
{
#ifdef DEBUG
    cout << "assign instace detected " << endl;
#endif
    Expression *var = new Expression();
   // var->expr.push_back(currentToken.lexeme);
   // 
    next();
    while (match(type ::COMMA))
    {
        next();
        if (match(type::SEMICOLON) || match(type::ASSIGN))
        {
            break;
        }
        else if (match(type::IDENTIFIER))
        {
            //var->expr.push_back(currentToken.lexeme);
            eval(type::IDENTIFIER, "expected variable name ");
        }
        else
        {
            Error("only identifier is allowed but got " + currentToken.lexeme);
        }
    }

    return var;
}

Expression *Parser::parseAssign()
{
#ifdef DEBUG
    cout << "assignment detected " << endl;
#endif
    Expression *t = new Expression();
    t->node = node_type::ASSIGN_NODE;
    eval(type::ASSIGN,"expected assign");
    t->expr1= expr();
    if(match(type::TO)||match(type::AS))
    {
        //loop until stop words
        next();
    }
    t->token=currentToken;
    eval(type::IDENTIFIER,"expected variable name");
    if(match(type::SEMICOLON))
    {
        next();
    }
    return t;
}


Expression *Parser::parseLeft()
{
    Expression *t = nullptr;
    if (match(type::L_SQ_BRACE))
    {
        t = parseArrayExpr();
    }
    return t;
}


bool Parser::isValid(type t)
{
    return (t == type::STRING,
            t == type::FLOAT,
            t== type::INT,
            t == type::COMMA || //, is optional
            t == type::LESS_THAN ||
            t == type::LESS_THAN_EQ ||
            t == type::GREATER_THAN ||
            t == type::GREATER_THAN_EQ ||
            t == type::OR ||
            t == type::AND ||
            t == type::NOT ||
            t == type::EQUALS ||
            t == type::NOT_EQUAL);
}

bool Parser::isInvalid(type t)
{
    return (t == type::RPAR ||
            t == type::RBRACE ||
            t == type::LBRACE ||
            t == type::AS || //stop word
            t == type::TO || //stop word
            t == type ::R_SQ_BRACE ||
            t == type::SEMICOLON);
}

// vector<VarDecl*>
Expression *Parser::parseArrayExpr(std::string array_name)
{
    Expression *a = new Expression();
    a->data= array_name;
    eval(type::L_SQ_BRACE, "expected '['");
    a->expr.push_back(expr());
    eval(type::R_SQ_BRACE, "expecting a ] / rbrace");
    return a;
}

Expression* Parser::expr()
{
    Expression *b = new Expression();
        b->node = node_type::BLOCK_NODE;
    if (isInvalid(currentToken.token_type))
    {
        cout << "expr " << endl;
        return nullptr;
    }
    else
    {
        
        while (!isInvalid(currentToken.token_type)||match(type::COMMA))
        {
          switch(currentToken.token_type)
          {
           case type::INT:
           {
            Expression *d =new Expression();
             d->token = currentToken;
             d->node = node_type::INT_NODE;
             next();
             b->expr.push_back(d);
             break; 
           }
           case type::COMMA:
           {
               next();
               break;
           }
            case type::STRING:
           {
             Expression *d =new Expression();   
             d->token = currentToken;
             d->node = node_type::STR_NODE;
             next();
             b->expr.push_back(d);           
             break; 
           }
           case type::FLOAT:
           {
            Expression *d =new Expression();    
             d->token = currentToken;
             d->node = node_type::FLOAT_NODE;
             next();
            b->expr.push_back(d);
             break; 
           }
           case type::TRUE:
           {
            Expression *d =new Expression();    
             d->token = currentToken;
             d->node = node_type::TRUE_NODE;
             next();
            b->expr.push_back(d);
             break; 
           }  
           case type::FALSE:
           {
            Expression *d =new Expression();    
             d->token = currentToken;
             d->node = node_type::FALSE_NODE;
             next();
            b->expr.push_back(d);
             break; 
           }                               
           case type::IDENTIFIER:
          {
                std::string id = currentToken.lexeme;
                next();
                if (match(type::IDENTIFIER))
                {
                b->expr.push_back(parseClassInstance(id));
                break;
                }
                else if (match(type::LPAR) || match(type::DOT))
                {
                    b->expr.push_back(parseCallStatement(id));
                    break;
                }
                else
                {
                    b->expr.push_back(varCall(id));
                    break;
                }
    }           
           default:
           {
            cout <<"something wrong in vp "<<(int)currentToken.token_type<<endl;
               break;
           }
        }
            cout <<"its okey machi"<<currentToken.lexeme<<endl;                      
        }

    }
    
    return b;
}

Expression *Parser::varCall(std::string var)
{
    //eval(type::IDENTIFIER, "expected variable name");
    Expression *call = new Expression();
    call->token = currentToken;
    return call;
}
// vector<VarDecl*>
Expression *Parser::parseArrayExpr()
{
    Expression *a = new Expression();
    eval(type::L_SQ_BRACE, "expected '['");
    a->expr.push_back(this->expr());
    eval(type::R_SQ_BRACE, "expecting a ] / rbrace");
    return a;
}

Expression *Parser::statements()
{
#ifdef DEBUG
    std::cout << currentToken.lexeme << " >> type : " << (int)currentToken.token_type << "\tparseStatement" << std::endl;
#endif
    Expression *p = nullptr;
    switch (currentToken.token_type)
    {
    case type::FUNCTION:
    {
        p = parseFunctionDecl();
        break;
    }
    case type::ENUM:
    {
        p = this->parseEnumClass();
        break;
    }
    case type::COMMA:
    {
        next();
        break;
    }
    case type::ASSIGN:
    {
        p= this->parseAssign();
        break;
    }    
    case type::SEMICOLON:
    {
        next();
        break;
    }
    case type::USING:
    {
        p = parseRequireExpr();
        break;
    }
    case type::CLASS:
    {
        p = ClassDecl();
        break;
    }
    case type::ERROR:
    {
        cerr << "error : " << currentToken.lexeme << endl;
        p = nullptr;
        throw ParseException("lexing error");
        break;
    }
    case type::IDENTIFIER:
    {
        std::string id = currentToken.lexeme;
        next();
        if (match(type::IDENTIFIER) || match(type::LESS_THAN))
        {
            p = parseClassInstance(id);
            break;
        }
        else if (match(type::LPAR) || match(type::DOT))
        {
            p = parseCallStatement(id);
            break;
        }
        else
        {
            Error("syntax error : or [ or ( or . expected");
        }
    }
    case type::IF:
    {
        p = parseIf();
        break;
    }
    case type::WHILE:
    {
        p = parseWhileExpr();
        break;
    }
    case type::RETURN:
    {
        p = parseReturnExpr();
        break;
    }
    default:
    {
        throw "something wrong in parsing";
        break;
    }
    }

    return p;
}

Expression *Parser::parseType()
{
    Expression *t = new Expression();
    if (match(type::IDENTIFIER))
    {
        Token tk;
        tk.lexeme = currentToken.lexeme;
        tk.token_type = type::CLASS;
        t->token = tk;
        next();
    }
    else
    {
        cerr << "invalid datatype found" << endl;
    }
    return t;
}


// FunctionCall*
Expression *Parser::parseCallStatement(std::string func_name)
{
#ifdef DEBUG
    std::cout << currentToken.lexeme << " >> type : " << (int)currentToken.token_type << "\tparseFunctionCall" << std::endl;
#endif
    Expression *f = new Expression();
    f->data = func_name;
    f->node = node_type::FUN_CAL;
    if (match(type::LPAR))
    {
        next();
        f->expr.push_back(this->expr());
        eval(type::RPAR, "expected ')'L");
        return f;
    }
    else
    {
        cerr << "error on  function call of " << currentToken.lexeme << endl;
    }
    if(match(type::SEMICOLON))
    {
        next();
    }
    return f;
}

// FunctionDecl*
Expression *Parser::parseFunctionDecl()
{
    Expression *p = new Expression();

    eval(type::FUNCTION, "expected function keyword");
    p->data = currentToken.lexeme;
    eval(type::IDENTIFIER, "expected 'function name'");
    //eval(type::AS, "expected 'function name'");
    p->expr.push_back(parseBlock());
    return p;
}

// IfOrElse*
Expression *Parser::parseIf()
{
    cout << "detect if ok" << endl;
    //check if is found or not before else at gen
    Expression *p = new Expression();
    if (match(type::IF))
    {
        next();
        p->expr.push_back(expr());
        p->expr.push_back(parseBlock());

        if (match(type::ELSE))
        {
            next();
            if (match(type::IF))
            {
                cout << "detect else if ok" << endl;
                p->expr.push_back(this->parseIf());
            }
            else
            {
                cout << "detect else ok " << currentToken.lexeme << endl;
                p->expr.push_back(parseBlock());
            }
        }
    }

    return p;
}

Expression *Parser::parseReturnExpr()
{ //eat return
Expression *r = new Expression();
    eval(type::RETURN, "return expected ");
     r->expr.push_back(this->expr());
 if(match(type::SEMICOLON))
 {
     next();
 }
    return r;
}

Expression *Parser::parseEnumClass()
{
    Expression *l = new Expression;
    eval(type::ENUM, "enum expected ");
    eval(type::CLASS, "class expected ");
    std::string enum_class_name = currentToken.lexeme;
    eval(type::IDENTIFIER, "expected enum class name");
    Token k = currentToken;
    eval(type::LBRACE, "an Enum class must have a'{' after class name");
    while (k.token_type != type::RBRACE)
    {
        eval(type::AS, "expected as");
        eval(type::IDENTIFIER, "expected enum variable name");
         l->token =currentToken;
        eval(type::COMMA, "Expected a comma");
       
    }
    if (match(type::RBRACE))
    {
        next();
    }
    return l;
}

Expression *Parser::parseRequireExpr()
{
    //eat require
    eval(type::USING, "expected using");
    Expression *p = new Expression();
    
    p->expr1 = new Expression();
    p->node = node_type::MOD_CALL;
    p->expr1 = this->expr();
     if(match(type::SEMICOLON))
     {
         next();
     }
     
    return p;
}
