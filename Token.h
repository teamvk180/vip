/** 
  * Description: Header file for class Token.
  * Token class is used as a container for the attributes of a token for the 'little language'
  */

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
typedef struct
{
	std::vector<std::string> buff;
} driver_b;

//Token types
const int SEMICOLON = 1;
const int ASSIGNMENT = 2;
const int GREATER_THAN = 3;
const int GREATER_THAN_EQ = 4;
const int NOT_EQUAL = 6;
const int LESS_THAN = 7;
const int LESS_THAN_EQ = 8;
const int ADD = 9;
const int SUBTRACT = 10;
const int MULTIPLY = 11;
const int DIVIDE = 12;
const int AND = 13;
const int OR = 14;
const int NOT = 15;
const int IN = 16;
const int TAR_ID = 17;
const int L_BRACK = 18;
const int R_BRAK = 19;
const int L_PAREN = 20;
const int R_PAREN = 21;
const int L_BRACE = 22;
const int R_BRACE = 23;
const int LOOP = 24;
const int CHECK = 26;
const int SERVE = 27;
const int OUT = 28;
const int COMMENT = 29;
const int ID = 30;
const int INT_TYPE = 31;
const int STRING_TYPE = 32;
const int FLOAT_TYPE = 33;
const int BOOL_FALSE = 34;
const int BOOL_TRUE = 35;
const int EOP = 36;
const int ERROR = 37;
const int COMPARE = 38;
const int EXTENDS = 39;
const int COMMA = 40;
const int NAMESPACE = 41;
const int RETURN = 42;
const int STR_PUNCT = 43;
const int DOT = 44;
const int USING = 45;
const int AS = 46;
const int TYPE_STRING = 47;
//const int TYPE_FUNC = 48;
const int TYPE_METHOD = 49;
const int BUFFER_TYPE = 50;
const int EOS = 51;
const int DOLLAR = 52;
const int BUFFER = 53;
//inverse
/*
const int BACKSLASH_SEMICOLON = 54;
const int BACKSLASH_ASSIGNMENT = 55;
const int BACKSLASH_GREATER_THAN = 56;
const int BACKSLASH_GREATER_THAN_EQ = 57;
//const int EQUAL = 5;
const int BACKSLASH_NOT_EQUAL = 58;
const int BACKSLASH_LESS_THAN = 59;
const int BACKSLASH_LESS_THAN_EQ = 60;
const int BACKSLASH_ADD = 61;
const int BACKSLASH_SUBTRACT = 62;
const int BACKSLASH_MULTIPLY = 63;
const int BACKSLASH_DIVIDE = 64;
const int BACKSLASH_AND = 65;
const int BACKSLASH_OR = 66;
const int BACKSLASH_NOT = 67;
const int BACKSLASH_IN = 68;
const int BACKSLASH_TAR_ID = 69;
const int BACKSLASH_L_BRACK = 70;
const int BACKSLASH_R_BRAK = 71;
const int BACKSLASH_L_PAREN = 72;
const int BACKSLASH_R_PAREN = 73;
const int BACKSLASH_L_BRACE = 74;
const int BACKSLASH_R_BRACE = 75;
const int BACKSLASH_LOOP = 76;
const int BACKSLASH_CHECK = 77;
const int BACKSLASH_SERVE = 78;
const int BACKSLASH_OUT = 79;
const int BACKSLASH_COMMENT = 80;
const int BACKSLASH_ID = 81;
const int BACKSLASH_INT_TYPE = 82;
const int BACKSLASH_STRING_TYPE = 83;
const int BACKSLASH_FLOAT_TYPE = 84;
const int BACKSLASH_BOOL_FALSE = 85;
const int BACKSLASH_BOOL_TRUE = 86;
const int BACKSLASH_EOP = 87;
const int BACKSLASH_ERROR = 88;
const int BACKSLASH_COMPARE = 89;
const int BACKSLASH_EXTENDS = 90;
const int BACKSLASH_COMMA = 91;
const int BACKSLASH_NAMESPACE = 92;
const int BACKSLASH_RETURN = 93;
const int BACKSLASH_STR_PUNCT = 94;
const int BACKSLASH_DOT = 95;
const int BACKSLASH_USING = 96;
const int BACKSLASH_AS = 97;
const int BACKSLASH_TYPE_STRING = 98;
const int BACKSLASH_TYPE_FUNC = 99;
const int BACKSLASH_TYPE_CLASS = 100;
const int BACKSLASH = 101;
const int BACKSLASH_BACKSLASH = 102;
//some advanced fuzzy token's
const int NEGATION = 103;					   //~
const int BACKSLASH_NEGATION = 104;			   //\~
const int EQUIVALANCE = 105;				   //<=>
const int BACKSLASH_EQUIVALANCE = 106;		   //\<=>
const int GIVES = 107;						   //<-
const int BACKSLASH_GIVES = 108;			   //\<-
const int IMPLIES = 110;					   //->
const int DOUBLE_GRATER_THAN = 111;			   //>>
const int BLACKSLASH_DOUBLE_GRATER_THAN = 112; //\>>
const int DOUBLE_LESSER_THAN = 113;			   //<<
const int BLACKSLASH_LESSER_THAN = 114;		   //\<<
*/
//allocator
const int NEW = 115;
const int TYPE_CONST = 117;
const int TYPE_STAT = 118;
const int SIZEOF = 119;
const int BSIZEOF = 120;
const int FSIZEOF = 121;
const int TYPEOF = 122;
const int BTYPEOF = 123;
const int T_METHOD_DECL = 127;
const int PRIVATE = 129;
const int CHILD = 130;
const int CALL = 131;
const int SELF = 132;
const int EOH = 133;
const int POWER = 134;
const int IF = 135;
const int WHILE = 136;
const int ELSE = 137;
//const int FOR = 134;
const int DOUBLE_ADD = 138;
const int DOUBLE_SUBRACT = 139;
const int T_FILE = 140;
const int DRIVER = 141;
const int MOD = 142;
const int NEGATIVE_INT_TYPE = 143;
const int NEGATIVE_FLOAT_TYPE = 151;
const int TYPE_BOOL = 146;
/*
ast tokens not lexing tokens 
*/
const int LABEL_INVALID = 153;
const int TYPE_INT = 141;
const int TYPE_FLOAT = 142;
const int TYPE_VOID = 143;
const int TYPE_DRIVER = 144;
const int TYPE_INVALID = 145;
const int THIS = 146;
const int TYPE_NULL = 146;
const int BOOL_EXPR = 147;
const int TYPE_NEGATIVE_NUMBER = 148;
const int TYPE_MATH_ADD_EXPR = 149;
const int TYPE_MATH_MUL_OR_DIV_OP = 150;
const int CALL_EXPR = 151;
const int AT_THE_HEAD = 0;
const int AT_THE_MAIN = 2;
const int AT_THE_BODY = 1;
const int AT_LINKER = 4;
const int INSIDE_METHOD_ASSIGNMENT = 45;
//end of code ie code,<--EOC
const int EOC = 148;
class Token
{
public:
	//default constructor
	Token();

	//constructor with line, column, type, and lexeme params
	Token(int type, int line, int col, std::string lexeme);
	Token(int type, std::string conf_type, int line, int col, std::string lexeme);

	/*
		 * Getter for the Token's type
		 * Return: The integer value for the type is returned
		 */
	int type() const;

	/*
		 * Getter for the line in the file in which the Token occurs
		 * Return: Line number for Token
		 */
	int line() const;

	/*
		 * Getter for the column in the file in which the Token occurs
		 * Return: Column number for Token
		 */
	int column() const;

	/*
		 * Getter for the lexeme of the Token
		 * Return: A string which contains the Token's Lexeme
		 */
	std::string lexeme() const;
	std::string conf_type() const;
	/*
		 * Sets the token's lexeme
		 */
	void setLexeme(std::string theLexeme);
	void setType(int this_token_type);
	void setLine(int this_token_line);
	void setColumn(int this_token_column);

private:
	//member var for type
	int token_type;

	//member var for line
	int token_line;

	//member var for column
	int token_column;
	std::string token_conf_type;
	//member var for the Token's lexeme
	std::string token_lexeme;
};

#endif
