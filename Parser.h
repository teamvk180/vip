#ifndef PARSER_H
#define PARSER_H
#define DEBUG 45543
#include <vector>
#include "Lexer.h"
#include <stdbool.h>
#include "Token.h"
#include <string>
#include <cstdlib>
#include "Exception.h"
#include "SymbolTable.h"
#include <istream>
#include <vector>
#include <queue>
#include <fstream>
#include <map>
#include "ast.h"
#include <stack>
#include "load.h"
using namespace std;

/*
typedef struct
{
    int token_type;
    int token_line;
    int token_column;
    std::string lexeme;
} token_cache;
*/

/**
 *    _VIP global registry_
 *          |
 * (cache)--|
 *          |
 *          | 
 *         /\
 *        /  \
 *       /    \             
 * (signal)    \
 *              \
 *             (objects)
 */

typedef struct __VIP_T_OBJECT __VIP_T_OBJECT;
struct __VIP_T_OBJECT //object
{
    const char *__VIP_HEAD;        //name of the object
    const char *__VIP_BODY;        //value or holding data may be an array
    const char *__VIP_OBJECT_TYPE; //int char float driver or method
    const char *_VIP_SCOPE;
    __VIP_T_OBJECT *next;
};

typedef struct __VIP_T_SIGNAL __VIP_T_SIGNAL; //object
struct __VIP_T_SIGNAL
{
    int _signal_; //signal
    int _type_;   //type
    __VIP_T_SIGNAL *next;
};
/*
template <typename T>
std::string ToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}
*/
class Parser
{
public:
    state_cache format_tokens();
    vector<Expression *> ast_node;
    // queue<pair<int, vector<Expression *>>> vip_expr_stac__;
    //vector<pair<int, vector<Expression *>>> vip_expre_vector__;
    inline bool is_exist_(const std::string &name)
    {
        if (FILE *file = fopen(name.c_str(), "r"))
        {
            fclose(file);
            return true;
        }
        else
        {
            return false;
        }
    }
    //constructor, takes ref to Lexer as argument
    Parser(loader &load);
    /* Function to parse stream of tokens
		 * Return: A StmtList object if successfull
		 * and NULL if otherwise
		 */
    std::string link = "\0";
    //std::string make_link();
private:
    int gen_idr();
    std::string current_method;
    std::string current_calll;
    void update();
    void outdate();
    /*
1 	()   []   ->   .   :: 	Function call, scope, array/member access
2 	!   ~   -   +   *   &   sizeof   type cast   ++   --   	(most) unary operators, sizeof and type casts (right to left)
3 	*   /   % MOD 	Multiplication, division, modulo
4 	+   - 	Addition and subtraction
5 	<<   >> 	Bitwise shift left and right
6 	<   <=   >   >= 	Comparisons: less-than and greater-than
7 	==   != 	Comparisons: equal and not equal
8 	& 	Bitwise AND
9 	^ 	Bitwise exclusive OR (XOR)
10 	| 	Bitwise inclusive (normal) OR
11 	&& 	Logical AND
12 	|| 	Logical OR
13 	? : 	Conditional expression (ternary)
14 	=   +=   -=   *=   /=   %=   &=   |=   ^=   <<=   >>= 	Assignment operators (right to left)
15 	, 	Comma operator
*/
    std::map<int, int> OperatorPrecedence = {
        {(int)ASSIGNMENT, 0},
        {(int)COMPARE, 0},
        {(int)LESS_THAN, 1},
        {(int)GREATER_THAN, 1},
        {(int)GREATER_THAN_EQ, 1},
        {(int)LESS_THAN_EQ, 1},
        {(int)NOT_EQUAL, 1},
        {(int)ADD, 2},
        {(int)DOUBLE_ADD, 2},
        {(int)DOUBLE_SUBRACT, 2},
        {(int)SUBTRACT, 2},
        {(int)MULTIPLY, 3},
        {(int)DIVIDE, 3},
        {(int)POWER, 4},
        {(int)AND, 5},
        {(int)OR, 5},

    };
    int get_precedence(int op) { return OperatorPrecedence[op]; }
    //data member of type lexer
    //stmt statment;
    loader &lex;
    //maintab ASTList
    //data member for the current token that is being Parsed
    Token currentToken;
    /*  Determines if current token has correct token type
		 *  Param: an int for tokenType, and a string for an err message
		 *  Post: if currentToken is of wrong type, Error is called
		 */
    bool eval(int token_type, const std::string errorMessage);
    bool eval_(int token_type, const std::string errorMessage);
    bool match(int token_type);
    bool match_(int token_type);
    //bool tab_up(string method_name);
    //bool var_tab_up(std::string identifier_name);
    //bool call_tab_up(std::string identifier_name);
    bool match(int token_type1, int token_type2);
    bool match(int token_type1, int token_type2, int token_type3);
    bool match(int token_type1, int token_type2, int token_type3, int token_type4);
    bool match(std::string lexme);
    /* Throws exception and couts error message
		 * Pre: invalid token detected
		 * Throw: ParseException
		 */
    void Error(const std::string &errMessage);
    //returns a token with the correct type
    void stmtsTail();
    //registering variables
    size_t brack_ = 0;
    int call_ = 0;
    int paren_;
    int method_ = 0;
    bool eoh_parsed = false;
    bool finished;
    std::string current_method_name;
    size_t current_index_idr;
    void stamp()
    {
        std::fstream infile("internal\\lib_configs._vip_");
        if (infile.fail())
            throw MissingRequiredBasicBuiltInMethodsException("unable to read data in lib_config._vip_");
        size_t a;
        infile >> a;
        current_index_idr = a;
        return;
    }
    int get_type();
    //symbol_tab tab;
    // Expression mtab;
    Expression *parsid();
    Expression *parseIfExpr();
    Expression *parseIFtail();
    Expression *parseElseExpr();
    Expression *parseWhileExpr();
    Expression *statements();
    Expression *parseServeExpr();
    Expression *parseVarAssign();
    Expression *parseSelfExpr();
    std::string resolve_method_decl();
    std::string resolve_method_call();
    std::string resolve_name();
    Expression *parseReturn();
    Expression *parseStatic();
    Expression *expr();
    BlockExpr *parseBlock();
    BlockExpr *parseParenExpr();
    Expression *MethodCall();
    Expression *MethodDecl();
    Expression *eval_expr(int resolve_type);
    bool construct_();
    bool is_comma = false;
    bool is_internal_comma = false;
};
#endif
