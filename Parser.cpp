/**
  * File: Parser.cpp
  * Description: Implementation file for Parser.
  */

#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include <iostream>
#include "analyzer.h"
#include "load.h"
#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <sstream>
#include "Lexer.h"
//#define DEBUG 1
const std::string isSpace = "\t";
#include "Parser.h"

//tools for parsing
Parser::Parser(loader &load) : lex(load)
{
    this->stamp();
    cout << "total c(" << current_index_idr << ")" << endl;
    // lex.update_buffer();
    currentToken = lex.get_token();
#ifdef DEBUG
    cout
        << "takeing first input " << currentToken.lexeme() << endl;
#endif
    while (!match(EOS))
    {
        cout << "running ..   ";
        try
        {
#ifdef DEBUG
            cout << "iter " << endl;
#endif
            if (match(EOP))
                update();
            //break;
            if (match(EOS))
            {
                break;
            }
            Expression *stmt = this->statements();
            if (stmt != nullptr)
            {
                ast_node.push_back(stmt);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::string outcode = "\0";
    // Expression *t = new Expression();
    //t->set_tab(this->tab);
    for (size_t i = 0; i < ast_node.size(); i++)
    {
        cout << "evaluvating " << i << endl;
        if (ast_node[i] == nullptr)
        {
            Error("Compiler error (: ");
        }
        outcode += ast_node[i]->evaluvate();
    }

    //MakeNow *this_code = new MakeNow();
    //this_code->evaluvate();
    gen publish;
    publish.filePutContents("temp/in.cpp", "/*<vip-cleaning>*/", false);
    publish.filePutContents("temp/in.cpp", " ", false);
    publish.filePutContents("temp/in.cpp", "#include \"../driver/crsp_base_driver.h\"\n", true);
    publish.filePutContents("temp/in.cpp", "int main()\n{\n", true);
    publish.filePutContents("temp/in.cpp", " \nvip_base_ vip;\n", true);
    publish.filePutContents("temp/in.cpp", outcode, true);
    publish.filePutContents("temp/in.cpp", "\n}\n", true);
}

int Parser::gen_idr()
{
    current_index_idr++;
    return current_index_idr;
}
void Parser::stmtsTail()
{
#ifdef DEBUG
    cout << "one iteration finished .." << endl;
#endif
    if (currentToken.type() != EOS)
    {
        ;
    }
    else
    {
        //stop();
        return;
    }
}
void Parser::update()
{
    if (match(EOS))
    {
        return;
    }

    lex.update_buffer();
    currentToken = lex.get_token();
    return;
}

bool Parser::match_(int token_type)
{
    if (currentToken.type() == token_type)
    {
        update();
        //eval_(token_type, "expected a symbol");
        return true;
    }
    else
    {
        // Error("invalid token" + currentToken.lexeme());
        return false;
    }
}
bool Parser::match(int token_type)
{
    if (currentToken.type() == token_type)
    {
        return true;
    }
    else
    {
        //cout << "not mach idr =" << currentToken.type() << "get idr" << token_type << endl;
        // Error("invalid token" + currentToken.lexeme());
        return false;
    }
}
bool Parser::match(int token_type1, int token_type2)
{
    if (currentToken.type() == token_type1)
    {
        update();
        if (currentToken.type() == token_type2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // Error("invalid token" + currentToken.lexeme());
        return false;
    }
}
bool Parser::match(int token_type1, int token_type2, int token_type3)
{
    int position = lex.current_read_position();
    if (currentToken.type() == token_type1)
    {
        update();
        if (currentToken.type() == token_type2)
        {
            update();
            if (currentToken.type() == token_type3)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            lex.reset(position);
            return false;
        }
    }
    else
    {
        // Error("invalid token" + currentToken.lexeme());
        return false;
    }
}
bool Parser::match(int token_type1, int token_type2, int token_type3, int token_type4)
{
    if (currentToken.type() == token_type1)
    {
        update();
        if (currentToken.type() == token_type2)
        {
            update();
            if (currentToken.type() == token_type3)
            {
                update();
                if (currentToken.type() == token_type4)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        // Error("invalid token" + currentToken.lexeme());
        return false;
    }
}

bool Parser::match(std::string lexme)
{
    if (currentToken.lexeme() == lexme)
    {
        update();
        return true;
    }
    else if ((currentToken.lexeme()).size() <= 0)
    {
        update();
        throw SemanticError("invalid token found");
        return false;
    }
    else
    {
        // Error("expected '" + lexme + "' but detected " + currentToken.lexeme());
        return false;
    }
    return false;
}

void Parser::outdate()
{
    lex.outdate_buffer();
    return;
}
bool Parser::eval(int tokenType, const std::string errorMssg)
{
    if (match(tokenType))
        return true;
    else
    {
        Error(errorMssg);
        return false;
    }
}
bool Parser::eval_(int token_type, const std::string errorMessage)
{
    if (currentToken.type() == token_type)
    {
        update();
        return true;
    }
    else
    {
        Error(errorMessage);
        return false;
    }
}
void Parser::Error(const std::string &errorMssg)
{
    std::cout << errorMssg << std::endl;
    std::cout << "in file: " << lex.file_name() << " "
              << "Error line: " << currentToken.line() << " column: " << currentToken.column() << std::endl;
    throw ParseException("Parse Exception");
}
