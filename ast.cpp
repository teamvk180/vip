#include "ast.h"
#include <vector>
#define T_CALL 3 //load
#define T_LINK 2 //move
#define T_REQUEST 1
#define T_OBJECT 0
// Function to modify an identifier

bool Expression::insert(string kidentifier, string kscope, int type)
{
    Node mynode = Node(kidentifier, kscope, type);

    kmap.push_back(mynode);
    return true;
}
int Expression::find(std::string id)
{

    for (size_t i = 0; i <= kmap.size(); i++)
    {
        // cout << kmap[i].mIndex << "var : " << kmap[i].midentifier << endl;
        if (kmap[i].midentifier == id)
        {
            cout << "var : " + kmap[i].midentifier << endl;
            return kmap[i].mtype;
        }
    }
    return false;
}
std::string Expression::kind(std::string symbol)
{
    for (size_t i = 0; i <= kmap.size(); i++)
    {
        if (kmap[i].midentifier == symbol)
        {
            return kmap[i].mscope;
        }
    }
    return "-1";
}
bool Expression::modify(std::string id, string kscope, int type_)
{
    Node knode = Node(id, kscope, type_);
    for (size_t i = 0; i <= kmap.size(); i++)
    {
        if (kmap[i].midentifier == id)
        {
            kmap[i] = knode;
            return true;
        }
    }
    return false;
}
bool Expression::delete_this(std::string id)
{
    Node knode = Node("\0", "\0", 0);
    for (size_t i = 0; i <= kmap.size(); i++)
    {
        if (kmap[i].midentifier == id)
        {
            // kmap[i] = knode;
            kmap.erase(kmap.begin() + i);
            return true;
        }
    }
    return false;
}

std::string MethodStatement::evaluvate()
{
    this->set_context("METHOD_DECL");
    this->insert(method_name, "METHOD_DECL", 12);
    string ram = "vip.set_res(\"" + method_name + "\",1);" + isEnd;
    ram += "vip.set_req(500,1);" + isEnd;
    ram += this->method_body->evaluvate();
    ram += "vip.set_req(500,2);" + isEnd;
    return ram;
}
std::string Method_Call::evaluvate()
{
    this->insert(method_name, "METHOD_CALL", this->gen_idr());
    std::string ram = "\0";
    if (Method_body != nullptr)
    {
        ram += this->Method_body->evaluvate();
    }
    else
    {
        ;
    }

    ram += "vip.set_req(4,1);" + isEnd;
    return ram;
}
std::string variableExpr::evaluvate()
{
    this->set_context("VAR_EXPR");
    std::string out = "\0";
#ifdef DEBUG
    cout << "evaluvating " << mToken.lexeme() << endl;
#endif
    canalyzer.analyze_variable(mToken);
    switch (mToken.type())
    {
    case ID:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "1);" + isEnd;
        out += "vip.set_req(LOAD,1);" + isEnd;

        //means id for now not even relase replace gen_idr ->  symtab id
        break; //not implemented.
    }
    case INT_TYPE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "2);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case STRING_TYPE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "3);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case FLOAT_TYPE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "4);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case NEGATIVE_INT_TYPE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "5);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case NEGATIVE_FLOAT_TYPE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "6);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case TYPE_INT:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "7);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case TYPE_STRING:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "8);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case TYPE_CONST:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "9);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case TYPE_FLOAT:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "10);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case TYPE_INVALID:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "11);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case BOOL_TRUE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "12);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    case BOOL_FALSE:
    {
        out += "vip.set_res(\"" + mToken.lexeme() + "\"," + "13);" + isEnd;
        out += "vip.set_req(PUSH_,1);" + isEnd;
        break;
    }
    default:
        throw InvalidDataTypeException(mToken.lexeme() + " has a type mismatch" + ToString(mToken.type()));
        break;
    }
    return out;
}

void BinaryExpr::set_type(int mtype)
{
    this->type = mtype;
}
void BinaryExpr::set_lhs(Expression *mlhs)
{
    this->lhs = mlhs;
}
void BinaryExpr::set_rhs(Expression *mrhs)
{
    this->rhs = mrhs;
}
void AssignmentExpr::set_lhs(variableExpr *mfield)
{
    this->field = mfield;
}
void AssignmentExpr::set_rhs(Expression *moffset)
{
    this->offset = moffset;
}
std::string whileExpr::evaluvate()
{
    this->set_context("WHILE");
    std::string ram = "\0";
    if (condition != nullptr)
    {
        ram += this->condition->evaluvate();
    }
    else
    {
        throw BuiltINMethodInvalidCallException("while method requres an argument");
    }

    ram += "vip.set_req(78,1);" + isEnd; //200 is an expr indexed driver
    if (while_body != nullptr)
    {
        ram += this->while_body->evaluvate();
        ram += "vip.set_req(96,1);" + isEnd;
    }

    return ram;
}

std::string IfStatement::evaluvate()
{
    this->set_context("IF");
    std::string ram = "\0";
    if (if_block != nullptr)
    {
        ram += "vip.set_req(TEMP_ACTIVE,1);" + isEnd;
        ram += this->if_block->evaluvate();
        ram += "vip.set_req(DTEMP,1);" + isEnd; //jnz disable temp.
    }
    else
    {
        ;
    }
    if (condition != nullptr)
    {
        ram += this->condition->evaluvate();
        ram += "vip.set_req(JNZ,1);" + isEnd; //jnz driver to go label
    }
    else
    {
        throw BuiltINMethodInvalidCallException("if method requires an argument");
    }

    return ram;
}

std::string elseExpr::evaluvate()
{
    this->set_context("ELSE");
    std::string out = "\0";
    if (this->else_block != nullptr)
    {
        out += "vip.set_req(JZ,1);" + isEnd;
        out += else_block->evaluvate();
        out += "vip.set_req(DTEMP,1);" + isEnd;
    }
    else
    {
        ;
    }
    return out;
}

std::string SelfExpr::evaluvate()
{
    cout << "self called " << endl;
    this->set_context("SELF");
    std::string ram = "\0";
    if (this->argument != nullptr)
    {
        cout << "self called " << endl;
        ram += this->argument->evaluvate();
        ram += "vip.set_req(404,1);" + isEnd;
    }
    else
    {
        throw BuiltINMethodInvalidCallException("self method requires an arguement");
    }

    return ram;
}

std::string BinaryExpr::evaluvate()
{
    std::string ram = "\0";
    ram += lhs->evaluvate();
    ram += rhs->evaluvate();
    switch (type)
    {
    case ADD:
    {
        ram += "vip.set_req(15,1);" + isEnd;
        break;
    }
    case SUBTRACT:
    {
        ram += "vip.set_req(15,2);" + isEnd;
        break;
    }

    case MULTIPLY:
    {
        ram += "vip.set_req(15,3);" + isEnd;
        break;
    }

    case DIVIDE:
    {
        ram += "vip.set_req(15,4);" + isEnd;
        break;
    }

    case POWER:
    {
        ram += "vip.set_req(15,5);" + isEnd;
        break;
    }

    case LESS_THAN:
    {
        ram += "vip.set_req(15,6);" + isEnd;
        break;
    }

    case LESS_THAN_EQ:
    {
        ram += "vip.set_req(15,7);" + isEnd;
        break;
    }

    case GREATER_THAN:
    {
        ram += "vip.set_req(15,8);" + isEnd;
        break;
    }

    case GREATER_THAN_EQ:
    {
        ram += "vip.set_req(15,9);" + isEnd;
        break;
    }

    case COMPARE:
    {
        ram += "vip.set_req(15,10);" + isEnd;
        break;
    }

    case NOT_EQUAL:
    {
        ram += "vip.set_req(15,11);" + isEnd;
        break;
    }

    case AND:
    {
        ram += "vip.set_req(15,12);" + isEnd;
        break;
    }

    case OR:
    {
        ram += "vip.set_req(15,13);" + isEnd;
        break;
    }

    case ASSIGNMENT:
    {
        ram += "//vip.set_req(15,14);" + isEnd;
        break;
    }

    default:
    {
        throw InvalidOperationTypeException(ToString(type) + "this operation is not implemented ");
        break;
    }
    }

    return ram;
}
std::string AssignmentExpr::evaluvate()
{
    this->set_context("ASSIGN");
    std::string ram = "\0";
    this->insert(field->get_name(), "VAR_ASSIGN", gen_idr());
    ram += this->offset->evaluvate();
    ram += "vip.set_res(\"" + this->field->get_name() + "\",1);" + isEnd;
    ram += "vip.set_req(SAVE,1);" + isEnd;
    //ram += "vip.set_req(PUSH_,1);" + isEnd;
    return ram;
}

std::string serveStatement::evaluvate()
{
    std::string out = "\0";
    set_context("SERVE");
#ifdef DEBUG
    cout << "coding serve();" << endl;
#endif
    if (var->get_name() == "in")
    {
        cout << "in detected " << endl;
        out += vip_expr_->evaluvate();
        out += "vip.set_req(SCAN,1);" + isEnd;
    }
    else if (var->get_name() == "out")
    {
        cout << "out detected " << endl;
        out += vip_expr_->evaluvate();
        out += "vip.set_req(PRINT,1);" + isEnd;
    }
    else
    {
        throw InvalidArgumentCallException(var->get_name() + " driver does not exist ");
    }
    cout << "<<" + contest << ">> loaded" << endl;
    return out;
}

std::string BlockExpr::evaluvate()
{
    this->set_context("BLOCK");
    std::string ram = "\0";
    for (size_t i = 0; i != this->block.size(); i++)
    {
        ram += block[i]->evaluvate();
    }
    return ram;
}
int Expression::gen_idr()
{
    patti_ramu++;
    return patti_ramu;
}
std::string ReturnStatement::evaluvate()
{
    std::string rom = "\0";
    rom += this->ret_expr->evaluvate();
    rom += "vip.set_req(234,1);" + isEnd;
    return rom;
}