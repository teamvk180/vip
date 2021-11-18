#ifndef AST_H
#define AST_H
#include "Token.h"
#include "Exception.h"
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#define DEBUG 1
using namespace std;

enum node_type {
    IF_NODE,
    MOD_CALL, //using 'library.vp'
    BLOCK_NODE, // {--- block ---}
    WHILE_NODE,
    INT_NODE,
    TRUE_NODE,
    FALSE_NODE,
    STR_NODE,
    FLOAT_NODE,
    ASSIGN_NODE,
    FUN_CAL,
    FUN_DECL,
    VAR_ASSIGN,
    CLS_DECL,
    CLS_CAL,
    OBJ_DECL,
    OBJ_CAL,
};

class Expression;
class Expression 
{
public:
    Expression() = default;
    ~Expression() = default;
    Token token;
    Expression *expr1=nullptr; //head
    Expression *expr2=nullptr; //body
    Expression *expr3=nullptr; //extras
    Expression *expr4=nullptr;
    std::string data;
    vector<Expression*> expr;
    node_type node;   
    Expression* evaluvate();
};


#endif