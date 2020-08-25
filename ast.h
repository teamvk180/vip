#ifndef AST_H
#define AST_H
#include "generator.h"
#include "SymbolTable.h"
#include "Token.h"
#include "Exception.h"
#include <string>
#include "analyzer.h"
#include <map>
#include "CodeGen.h"
#include <vector>
#include <queue>
using namespace std;
typedef struct
{
    int state;
    //std::vector<Token> tok;
    // queue<pair<int, Expression *>>> mk;
} state_cache;

class AST
{
public:
    Analyzer canalyzer;
    CodeGen code;
    size_t patti_ramu = 0;
    int context_type;
    std::string contest = "\0";
    std::string result = "<VIP>";
    virtual std::string evaluvate() = 0;
    void set_context(std::string in) { this->contest = in; }
    std::string get_context() { return this->contest; }
    virtual ~AST(){};
    static void record(const std::string &var, std::string value);
};
class Expression : public AST
{
public:
    ~Expression() {}
    std::string evaluvate()
    {
        std::string r = "/*<VIP-overrider-not-found>  " + contest + "*/\n";
        return r;
    }
    int gen_idr();
    struct Node
    {
    public:
        // Token mtoken;
        string midentifier, mscope;
        int mtype;
        Node(string identifier, string scope, int type)
            : midentifier(identifier), mscope(scope), mtype(type)
        {
        }
        void print()
        {
            cout << "key Name:" << midentifier
                 << "\nScope: " << mscope
                 << "\ntype : " << mtype << endl;
        }
        //friend class Expression;
    };

    bool insert(string kidentifier, string kscope, int type);
    int find(std::string id);
    bool modify(std::string id, string kscope, int type_);
    bool delete_this(std::string id);
    std::string kind(std::string symbol);
    std::vector<Node> kmap;
};
class BlockExpr : public Expression
{
private:
    vector<Expression *> block;

public:
    BlockExpr(){};
    std::string evaluvate();
    void set_block(vector<Expression *> bl)
    {
        this->block = bl;
    };
};
class variableExpr : public Expression
{
private:
    Token mToken;
    std::string mvar;
    int idr;
    int context_;

public:
    variableExpr() {}
    void set_variable(Token t)
    {
        this->mToken = t;
    }
    void set_name(std::string var)
    {
        this->mvar = var;
    }
    void set_id(int id)
    {
        this->idr = id;
    }
    /*
    void set_context(int contex_type)
    {
        this->context_ = contex_type;
    }
    */
    int get_type()
    {
        return mToken.type();
    };
    std::string get_name()
    {
        return mToken.lexeme();
    };
    std::string evaluvate();
};

class unaryExpr : public Expression
{
public:
    std::string evaluvate()
    {
        std::string doc = "/*<VIP-unary-not-implemented>*/";
        return doc;
    };
};

class AssignmentExpr : public Expression
{
public:
    AssignmentExpr() {}
    std::string evaluvate();
    void set_lhs(variableExpr *mfield);
    void set_rhs(Expression *moffset);

private:
    Expression *offset;
    variableExpr *field;
};

class BinaryExpr : public Expression
{
private:
    Expression *lhs;
    Expression *rhs;
    int type;

public:
    //explicit ArithmaticExpr(int mtype, Expression *mlhs, Expression *mrhs) : type(static_cast<int>(mtype)), lhs(mlhs), rhs(mrhs) {}
    BinaryExpr(){};
    std::string evaluvate();
    void set_type(int mtype);
    void set_lhs(Expression *mlhs);
    void set_rhs(Expression *mrhs);
};

class brackExpr : public Expression
{
private:
    vector<Expression *> expr_;

public:
    void set_expr(vector<Expression *> exp)
    {
        this->expr_ = exp;
    };
    std::string evaluvate();
};
class MethodStatement : public Expression
{
public:
    MethodStatement() {}
    void set_method_name(string name)
    {
        this->method_name = name;
    }
    std::string evaluvate();
    void set_body(BlockExpr *exp)
    {
        this->method_body = exp;
    }

private:
    std::string method_name;
    BlockExpr *method_body;
};
class Method_Call : public Expression
{
private:
    std::string method_name;
    BlockExpr *Method_body;

public:
    Method_Call(){};
    std::string evaluvate();
    void set_method_name(std::string name)
    {
        this->method_name = name;
    };
    void set_params(BlockExpr *exp)
    {
        this->Method_body = exp;
    }
};

class IfStatement : public Expression
{
private:
    //brackExpr *if_;
    BlockExpr *if_block;
    Expression *condition;

public:
    std::string evaluvate();
    void set_if_type(BlockExpr *_if_)
    {
        this->if_block = _if_;
    }
    void set_condition(Expression *_cond_)
    {
        this->condition = _cond_;
    }
    //void set_expr(brackExpr *exp) { this->if_ = exp; };
};
class elseExpr : public Expression
{
private:
    BlockExpr *else_block;

public:
    std::string evaluvate();
    void set_block(BlockExpr *_blk_)
    {
        this->else_block = _blk_;
    }
};
class whileExpr : public Expression
{
private:
    BlockExpr *while_body;
    Expression *condition;

public:
    std::string evaluvate();
    void set_body(BlockExpr *_body_)
    {
        this->while_body = _body_;
    }
    void set_condition(Expression *_cond_)
    {
        this->condition = _cond_;
    }
};
class serveStatement : public Expression
{
private:
    variableExpr *var;
    Expression *vip_expr_;

public:
    //void set_type(std::string type) { this->type = type; }
    void set_service(variableExpr *mvar)
    {
        this->var = mvar;
    }
    void set_expr(Expression *vip_expr)
    {
        this->vip_expr_ = vip_expr;
    }
    std::string evaluvate();
};
class ReturnStatement : public Expression
{
private:
    BlockExpr *ret_expr;
    int context;

public:
    void set_context(int type)
    {
        this->context = type;
    }
    void set_expr(BlockExpr *return_expr)
    {
        this->ret_expr = return_expr;
    }
    std::string evaluvate();
};
class TernaryExpr : public Expression
{
private:
    Expression *l, *m, *r;
    int type;

public:
    TernaryExpr(){};
    std::string evaluvate()
    {
        throw BuiltINMethodInvalidCallException("this service is not implemented  till this update.");
    };
    void set_type(int mtype)
    {
        this->type = mtype;
    };
    void set_lhs(Expression *mlhs)
    {
        this->l = mlhs;
    };
    void set_mhs(Expression *mmhs)
    {
        this->m = mmhs;
    };
    void set_rhs(Expression *mrhs)
    {
        this->r = mrhs;
    };
};
class SelfExpr : public Expression
{

private:
    BlockExpr *argument;

public:
    SelfExpr() {}
    void set_argument(BlockExpr *arg) { arg = this->argument; }
    std::string evaluvate();
};
#endif