/** 
  * Description: Header file for class Lexer. 
  * Class Lexer is used to convert written programs into its token stream.
  */
#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <sstream>
#include <iterator>
#include <ostream>
#include "Token.h"
#include "load.h"
#include <istream>
#include <stack>
using namespace std;
typedef struct
{
    std::string file_name;
    int current_line;
    int current_column;
} file_struct;

typedef struct
{
    //member var for type
    int token_type;

    //member var for line
    int token_line;

    //member var for column
    int token_column;

    //member var for the Token's lexeme
    std::string token_lexeme;
    std::string file_name;

} container;
class Lexer
{
public:
    //constructor
    Lexer(std::ifstream &input_stream);
    /* Returns the next token
		 * Return: The next token in the stream 
		 */
    Token next_token();
    Token get_token();
    bool areParanthesisBalanced();
    bool is_alphabet(const std::string &str);
    std::vector<container> source;

private:
    /* Helper function to move to next character in the file stream
		 * Pre: Stream is at a position in the file stream
		 * Post: cursor is taken to the next non new line character
		 * Return: The next character
		 */
    Token load_identifier(const std::string &str);
    char getNextChar();
    //member variable for the current line in the file stream
    int current_line;
    loader file_stream;
    //member variable for the current column in the file stream
    int current_column;
    //current reading string
    std::string current_string;
    //The ifstream that is to be tokenized
    std::ifstream &input_stream;
};
#endif
