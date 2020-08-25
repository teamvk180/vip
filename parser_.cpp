#include "parser.h"
#include "SymbolTable.h"
#include "VIP_signal.h"
#include <iostream>

Expression *Parser::statements()
{
#ifdef DEBUG
    cout << "statement found : " << currentToken.lexeme() << endl;
#endif
    switch (currentToken.type())
    {
    case IF:
    {
        return this->parseIfExpr();
        break;
    }
    case ELSE:
    {
        return this->parseElseExpr();
        break;
    }
    case RETURN:
    {
        return this->parseReturn();
        break;
    }
    case EOP:
    {
        update();
        break;
    }
    case EOS:
    {
        break;
    }
    case EOH:
    {
        update();
        eoh_parsed = true;
        finished = true;
        break;
    }
    case COMMA:
    {
        update();
        break;
    }
    case SERVE:
    {
        return this->parseServeExpr();
        break;
    }
    case WHILE:
    {
        return this->parseWhileExpr();
        break;
    }
    case ID:
    {
        return this->parsid();
        break;
    }
    case ERROR:
    {
        throw SemanticError(" error in " + currentToken.lexeme() + " at line :" + ToString(currentToken.line()) + " ,column :" + ToString(currentToken.column()));
        update();
        break;
    }
    default:
    {
#ifdef DEBUG
        cout << "default arrived  " << currentToken.lexeme() << endl;
#endif
        return this->expr();
    }
    }

    return nullptr;
}

Expression *Parser::parseStatic()
{
    /*  if (get_type() == T_VAR_TYPE)
    {
   */
    variableExpr *var = new variableExpr();
    var->set_variable(currentToken);
    update();
    return var;
    /*}
else
{
    //throw InvalidDataTypeException("conflicting datatype ");
    return nullptr;
}
*/
}

BlockExpr *Parser::parseParenExpr()
{
    BlockExpr *my_t = new BlockExpr();
    vector<Expression *> m_expr;
    eval_(L_BRACK, "expected '('");
    while (!match(R_BRAK))
    {
        Expression *t = this->expr();
        if (t != nullptr)
        {
            m_expr.push_back(t);
        }
        else
        {
            update();
        }
    }
    eval_(R_BRAK, "expected ')'");
    my_t->set_block(m_expr);
    return my_t;
}
BlockExpr *Parser::parseBlock()
{
    vector<Expression *> block;
    eval_(L_BRACE, "Expected '{'");
    while (!match(R_BRACE))
    {

        Expression *k = this->statements();
        if (k != nullptr)
        {
            block.push_back(k);
        }
    }
    eval_(R_BRACE, "expected '}'");
    BlockExpr *b = new BlockExpr();
    b->set_block(block);
    return b;
}

Expression *Parser::parseIfExpr()
{
#ifdef DEBUG
    cout << "if ent " << currentToken.lexeme() << endl;
    //set_signal *c = new set_signal(currentToken)
#endif
    if (eval_(IF, "expected if stmt") == true)
    {
        IfStatement *if_node = new IfStatement();
        Expression *condition = this->parseParenExpr();
        BlockExpr *if_part = this->parseBlock();
        vector<Expression *> jambavan_uir;
        if_node->set_if_type(if_part);
        if_node->set_condition(condition);
        return if_node;
    }
    else
    {
        return nullptr;
    }
}
Expression *Parser::parseIFtail()
{
    ;
}

Expression *Parser::parseElseExpr()
{
    cout << "else reached " << endl;
    eval_(ELSE, "expected else statement");
    elseExpr *else_part = new elseExpr();
    BlockExpr *els_y = this->parseBlock();
    else_part->set_block(els_y);
    return else_part;
}

Expression *Parser::parseWhileExpr()
{
    cout << "kk raja khe ladke kicker lagade " << endl;
    eval_(WHILE, "expected while");
    Expression *condition = this->parseParenExpr();
    BlockExpr *body = this->parseBlock();
    whileExpr *while_node = new whileExpr();
    while_node->set_condition(condition);
    while_node->set_body(body);
    return while_node;
}

Expression *Parser::MethodCall()
{
#ifdef DEBUG
    cout << "method call detect " << endl;
#endif
    Method_Call *t = new Method_Call();
    eval(ID, "expected Method name");
    std::string pinky = this->resolve_method_call();
#ifdef DEBUG
    cout << "now pink is :" << pinky << endl;
#endif
    //tab.insert(pinky, "METHOD_CALL", gen_idr());
    t->set_method_name(pinky);
    if (pinky != "\0")
        update();
    else
    {
        throw LogicError("invalid resolving of name Ex root.sub.another.method_name(params)");
    }
    BlockExpr *exp;
    t->set_params(this->parseParenExpr());
    return t;
}
std::string Parser::resolve_method_decl()
{
    std::string total_method_name = currentToken.lexeme();
    std::string currentlexme = currentToken.lexeme();
    Token t = lex.next();
    if (t.type() == L_BRACE)
    {
        return currentlexme;
    }
    else if (t.type() == DOT)
    {
        while (!match(L_BRACE))
        {
            update();
            if (currentToken.type() == ID)
                total_method_name += currentToken.lexeme();
            if (currentToken.type() == DOT)
                total_method_name += ".";
        }
        return total_method_name;
    }
    else
    {
        throw LogicError("invalid method name unable to decl");
    }
}

std::string Parser::resolve_method_call()
{
#ifdef DEBUG
    cout << "resolving name of the method " << endl;
#endif
    std::string total_method_name = currentToken.lexeme();
    std::string currentlexme = currentToken.lexeme();
    Token t = lex.next();
#ifdef DEBUG
    cout << "lex ou " << t.lexeme() << endl;
#endif
    if (t.type() == L_BRACK)
    {
        return currentlexme;
    }
    else if (t.type() == DOT)
    {
        while (!match(L_BRACK))
        {
            update();
            if (currentToken.type() == ID)
                total_method_name += currentToken.lexeme();
            if (currentToken.type() == DOT)
                total_method_name += ".";
        }
        return total_method_name;
    }
    else
    {
        throw LogicError("invalid method name unable to resolve");
    }
}
Expression *Parser::MethodDecl()
{
    MethodStatement *t = new MethodStatement();
    eval(ID, "expected Method name");
    std::string doc_Ty = this->resolve_method_decl();
#ifdef DEBUG
    cout << " resolved name : " << doc_Ty << endl;
#endif
    //tab.insert(doc_Ty, "METHOD_DECL", gen_idr());
    t->set_method_name(doc_Ty);
    update();
    BlockExpr *st = this->parseBlock();
    t->set_body(st);
    return t;
}

Expression *Parser::parsid()
{
    Token m = lex.next();
#ifdef DEBUG
    cout << " next is " << m.lexeme() << endl;
#endif

    switch (m.type())
    {
    case L_BRACE:
    {
        return this->MethodDecl();
        break;
    }
    case L_BRACK:
    {
        return this->MethodCall();
        break;
    }
    case DOT:
    {
        return this->MethodCall();
        break;
    }

    case ASSIGNMENT:
    {
        //this->parseVarAssign();
        return this->parseVarAssign();
        break;
    }

    case COMMA:
    {
        variableExpr *r = new variableExpr;
        r->set_variable(currentToken);
        //r->set_context("EXPR");
        update();
        return r;
        break;
    }
    case R_BRAK:
    {
        variableExpr *r = new variableExpr;
        r->set_variable(currentToken);
        update();
        return r;
        break;
    }
    default:
    {
        break;
    }
        //which means id only ie variable call
    }
    variableExpr *r = new variableExpr;
    if (match(ID))
    {
        r->set_variable(currentToken);
        update();
        return r;
    }
    else
    {
        return nullptr;
    }
}

Expression *Parser::parseVarAssign()
{
#ifdef DEBUG
    cout << "assignment detected " << endl;
#endif
    eval(ID, "expected identifier");
    AssignmentExpr *t = new AssignmentExpr();
    variableExpr *lr = new variableExpr;
    Token tc;
    std::string piky = resolve_name();
    //tab.insert(piky, "ASSIGNMENT", gen_idr());
    tc.setLexeme(piky);
    tc.setType(ID);
    lr->set_variable(tc);
    lr->set_context("ASSIGNMENT");
    if (piky != "\0")
        update();
    else
    {
        throw "invalid name for assingment variable.";
    }

    eval_(ASSIGNMENT, "expected ':'");
    t->set_lhs(lr);
    t->set_rhs(this->parseParenExpr());
    if (t == nullptr)
    {
        throw InvalidOperationTypeException("assignment is invalid");
    }
    else
    {
        return t;
    }
}

Expression *Parser::parseSelfExpr()
{
    SelfExpr *self = new SelfExpr();
    eval_(SELF, "expected self");
    self->set_argument(this->parseParenExpr());
    cout << "done " << endl;
    if (self != nullptr)
        return self;
    else
        return nullptr;
}

Expression *Parser::expr()
{
#ifdef DEBUG
    std::cout << currentToken.lexeme() << "\tparseExpression" << std::endl;
#endif
    std::stack<Expression *> numStack;
    std::stack<int> opStack;
    while (true)
    {
        cout << "looping"
             << " " << currentToken.lexeme() << endl;
        switch (currentToken.type())
        {
        case EOP:
        {
            update();
            break;
        }
        case SELF:
        {
            numStack.push(this->parseSelfExpr());
            break;
        }
        case ID:
        {
            numStack.push(this->parsid());
            break;
        }
        case L_PAREN:
        {
            while (!match(R_PAREN))
            {
                numStack.push(this->parseBlock());
            }
            break;
        }
        case R_BRACE:
        {
            break;
        }
        case EOH:
        {
            update();
            eoh_parsed = true;
            break;
        }
        case R_PAREN:
        {
            break;
        }
        case EOS:
        {
            break;
        }
        case IF:
        {
            numStack.push(this->parseIfExpr());
            break;
        }
        case ELSE:
        {
            numStack.push(this->parseElseExpr());
            break;
        }
        case WHILE:
        {
            numStack.push(this->parseWhileExpr());
            break;
        }
        case SERVE:
        {
            numStack.push(this->parseServeExpr());
            break;
        }
        case INT_TYPE:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case STRING_TYPE:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case FLOAT_TYPE:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_STRING:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_THIS:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_INT:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_FLOAT:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_NEGATIVE_NUMBER:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case NEGATIVE_FLOAT_TYPE:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_BOOL:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case BOOL_FALSE:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case BOOL_TRUE:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case TYPE_CONST:
        {
            numStack.push(this->parseStatic());
            break;
        }
        case L_BRACK:
        {
            numStack.push(this->parseParenExpr());
            break;
        }
        case L_BRACE:
        {
            numStack.push(this->parseBlock());
            break;
        }
        case COMMA:
        {
            // expression end
            update(); // eat ',' or ';'
            continue;
        }
        case R_BRAK:
        {
            // expression end
            while (!opStack.empty())
            {
                char op = opStack.top();
                opStack.pop();
                Expression *l, *r;
                r = numStack.top();
                numStack.pop();
                l = numStack.top();
                numStack.pop();
                BinaryExpr *binExpr = new BinaryExpr();
                binExpr->set_lhs(l);
                binExpr->set_rhs(r);
                binExpr->set_type(op);
                numStack.push(binExpr);
            }
            if (!numStack.empty())
            {
                return numStack.top();
            }
            else
            {
                // std::cout<<"empty expression!"<<std::endl;
                return nullptr;
            }
        }
        default:
        {
            // std::cout<<"op"<<std::endl;
            if (!opStack.empty() &&
                get_precedence(opStack.top()) >= get_precedence(static_cast<int>(currentToken.type())))
            {
                char op = opStack.top();
                if (op == NOT)
                {
                    opStack.pop();
                    Expression *l;
                    l = numStack.top();
                    numStack.pop();
                    BinaryExpr *binExpr = new BinaryExpr();
                    binExpr->set_lhs(l);
                    binExpr->set_rhs(nullptr);
                    binExpr->set_type(op);
                    numStack.push(binExpr);
                }
                else if (op == CHECK)
                {
                    opStack.pop();
                    Expression *l, *m, *r;
                    r = numStack.top();
                    numStack.pop();
                    l = numStack.top();
                    numStack.pop();
                    TernaryExpr *tExpr = new TernaryExpr();
                    tExpr->set_lhs(l);
                    tExpr->set_mhs(m);
                    tExpr->set_rhs(r);
                    tExpr->set_type(op);
                    numStack.push(tExpr);
                }
                else
                {
                    opStack.pop();
                    Expression *l, *r;
                    r = numStack.top();
                    numStack.pop();
                    l = numStack.top();
                    numStack.pop();
                    BinaryExpr *binExpr = new BinaryExpr();
                    binExpr->set_lhs(l);
                    binExpr->set_rhs(r);
                    binExpr->set_type(op);
                    numStack.push(binExpr);
                }
            }
            opStack.push(static_cast<int>(currentToken.type()));
            update();
            break;
        }
        }
    }
}

std::string Parser::resolve_name()
{
    std::string total_method_name = currentToken.lexeme();
    std::string currentlexme = currentToken.lexeme();
    Token t = lex.next();
    if (t.type() == ASSIGNMENT)
    {
        return currentlexme;
    }
    else if (t.type() == DOT)
    {
        while (!match(ASSIGNMENT))
        {
            update();
            if (currentToken.type() == ID)
                total_method_name += currentToken.lexeme();
            if (currentToken.type() == DOT)
                total_method_name += ".";
        }
        return total_method_name;
    }
    else
    {
        return "\0";
    }
}

Expression *Parser::parseServeExpr()
{
    serveStatement *serv = new serveStatement();
    variableExpr *jock = new variableExpr();
    eval_(SERVE, "expected serve");
    eval_(L_BRACK, "Expected '('");
    jock->set_variable(currentToken);
    jock->set_context("SERVE");
    serv->set_service(jock);
    update();
    eval_(ASSIGNMENT, "expected an : symbol");
#ifdef DEBUG
    cout << "running for " << currentToken.lexeme() << endl;
#endif
    serv->set_expr(this->expr());
    eval_(R_BRAK, "expected ')'");
#ifdef DEBUG
    cout << "brack type :" << currentToken.lexeme() << endl;
#endif
    return serv;
}

Expression *Parser::parseReturn()
{
#ifdef DEBUG
    std::cout << currentToken.lexeme() << "\tparseFuncReturn" << std::endl;
#endif
    eval_(RETURN, "expected return "); // eat "return"
    eval_(ASSIGNMENT, "expected assignment after return");
    ReturnStatement *re = new ReturnStatement();
    BlockExpr *retExpr = this->parseParenExpr();
    if (retExpr != nullptr)
    {
        re->set_context(RETURN);
        re->set_expr(retExpr);
        return re;
    }
    else
    {
        return nullptr;
    }
}
