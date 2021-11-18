/** 
  * Description: Header file for class Token.
  * Token class is used as a container for the attributes of a token for the 'little language'
  */

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>

enum class type
{
	AS,//stop words
    TO,//stop words
	THEN,
	ERROR,
	IDENTIFIER,	   //$variable
	FUNCTION_CALL, // method_call()
	STD_FUNC_CALL,

	INT,
	STRING,
	FLOAT,
	LINK,  // @"https://www.xnovity.com/redirect"
	TRUE,  //1
	FALSE, //0
	VOID,  //null

	IF,
	ELSE,

	FOR, // for
	FOR_EACH,
	WHILE,

	DOT,		  //.
	DOUBLE_POINT, // ..

	ASSIGN,		  // assign
	EQUALS,		  // ==
	DOUBLE_ADD,	  // ++
	DOUBLE_MINUS, //--
	NEGATIVE_NUMBER,
	MEMBEROF, //::

	PLUS,  // +
	MINUS, // -
	STAR,  // *
	SLASH, // /
	POWER, // ^
	MOD,   // %
	CHECK, // ?

	LPAR,		// (
	RPAR,		// )
	LBRACE,		// {
	RBRACE,		// }
	L_SQ_BRACE, // [
	R_SQ_BRACE, // ]

	COMMA,	   // ,
	SEMICOLON, // ;

	GREATER_THAN,	 // >
	GREATER_THAN_EQ, // >=
	LESS_THAN,		 // <
	LESS_THAN_EQ,	 // <=
	OR,				 // |
	AND,			 // &
	NOT,			 // !
	NOT_EQUAL,		 //!=
	HASH,			 //#

	SELF,	// self
	THIS,	// this
	USING,	// USE
	RETURN, // return
	CALL,	//call
	OVERRIDE,
	FUNCTION, // function {}
	METHOD,
	USE,
	PROVIDE,
	CLASS,
	PARENT,
	CHILD,
	EXTENDS, // extends
	ENUM,	 //enum
	FIELD,
	STATIC,

	INT_CAST,	 //int
	STRING_CAST, //string
	FLOAT_CAST,	 //float
	BOOL_CAST,	 //bool
	CONST_CAST,	 //const
	VOID_CAST,	 //void
	METHOD_CAST, //method
	
	EOS,
	CREATE_INSTANCE, //create-instance
	CONSTRUCTOR,	 //constructor()
	DESTRUCTOR,		 // destructor
};

class Token
{
public:
	//default constructor
	Token();

	//constructor with line, column, type, and lexeme params
	Token(type Type, int line, int column, std::string Lexeme);
	//member var for type
	type token_type;
	//member var for line
	size_t current_line;

	size_t current_coloumn;
	std::string lexeme;
	std::string file;
};

#endif
