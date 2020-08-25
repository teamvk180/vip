#include <string>
#include <map>
#include <iterator>
using namespace std;
#include <vector>
#include "Lexer.h"
#include "Exception.h"
#include <exception>
#include <iostream>
#include <fstream>
Lexer::Lexer(std::ifstream &stream) : input_stream(stream)
{
    current_column = 0;
    current_line = 0;
}
Token Lexer::next_token()
{
    char c = getNextChar();
    //current_column++;
    Token t;
    std::string kstring;
    kstring = c;
    //if whitespace; get next char until not whitespace
    while (isspace(c))
    {
        c = getNextChar();
    }
    //single chars
    if (c == '/' && input_stream.peek() == '/')
    {
        while (input_stream.peek() != '\n')
            c = getNextChar();
        //c = getNextChar();
        current_line++;
        current_column = 0;
        return next_token();
    }
    /*
    if (c == '_')
    {
        while (c != '\n' || !isspace(c) ||
               input_stream.peek() == '_' ||
               c == '_' || isalnum(input_stream.peek()) || isalnum(c) || !isspace(input_stream.peek()))
        {
            c = getNextChar();
            kstring += c;
            if (c == '\n' || c == '\t' || isspace(c))
            {
                break;
            }
        }
        return Token(ID, current_column, current_line, kstring);
    }
    */
    if (c == ';')
    {
        t = Token(SEMICOLON, current_line, current_column, ";");
    }
    else if (c == ',')
    {
        t = Token(COMMA, current_line, current_column, ",");
    }
    else if (c == '^')
    {
        t = Token(POWER, current_line, current_column, "^");
    }
    else if (c == '%')
    {
        t = Token(MOD, current_line, current_column, "%");
    }
    else if (c == '$')
    {
        t = Token(DOLLAR, current_line, current_column, "$");
    }
    else if (c == '&')
    {
        t = Token(AND, current_line, current_column, "&");
    }
    else if (c == '|')
    {
        t = Token(OR, current_line, current_column, "|");
    }
    else if (c == '@')
    {
        ;
        // t = Token(LOOP, current_line, current_column, "@");
    }
    else if (c == '.')
    {
        t = Token(DOT, current_line, current_column, ".");
    }
    else if (c == '#')
    {
        t = Token(TAR_ID, current_line, current_column, "#");
    }
    else if (c == '+')
    {
        if (input_stream.peek() == '+')
        {
            t = Token(DOUBLE_ADD, current_line, current_column, "++");
            getNextChar();
        }
        else
            t = Token(ADD, current_line, current_column, "+");
    }
    else if (c == '-')
    {
        if (input_stream.peek() == '-')
        {
            t = Token(DOUBLE_SUBRACT, current_line, current_column, "++");
            getNextChar();
        }
        else if (c == '-' && isdigit((unsigned char)input_stream.peek()))
        {

            std::string theNumber = "";
            theNumber += c;
            bool hasDecimal = false;
            int firstLetterColumn = current_column;
            while (isdigit(input_stream.peek()) || input_stream.peek() == '.')
            {
                c = getNextChar();
                //block ensures only one decimal point or
                //Token type returned is ERROR
                if (c == '.')
                {
                    if (!hasDecimal)
                    {
                        theNumber += c;
                        hasDecimal = true;
                    }
                    else
                    {
                        //returns error if more than one decimal point
                        cout << "Error in line: " << current_line << "in column: " << current_column;
                        throw ReadingError("Invalid Decimal Number");
                        return Token(ERROR, current_line, firstLetterColumn, "Invalid Decimal Number");
                    }
                }
                else
                {
                    theNumber += c;
                }
            }
            //return correct type FLOAT_TYPE or INT_TYPE
            t = (hasDecimal) ? Token(NEGATIVE_FLOAT_TYPE, current_line, firstLetterColumn, theNumber) : Token(NEGATIVE_INT_TYPE, current_line, firstLetterColumn, theNumber);

            // t = Token(TYPE_NEGATIVE_NUMBER, current_line, current_column, "NEGATIVE_NUM");
        }
        else
            t = Token(SUBTRACT, current_line, current_column, "-");
    }
    else if (c == '*')
    {
        t = Token(MULTIPLY, current_line, current_column, "*");
    }
    else if (c == '/')
    {
        if (input_stream.peek() == '*')
        {
            std::string theStr = "";
            //make comment until another */
            while (c != '*' && input_stream.peek() != '/')
            {
                input_stream.get();
                if (c == '\n')
                {
                    c = getNextChar();
                    c = ' ';
                    current_line++;
                }
                current_column++;
            }
            // t = Token(COMMENT, current_line, firstLetterColumn, "");
            input_stream.get();
            current_column++;
            return next_token();
        }
        else
        {
            t = Token(DIVIDE, current_line, current_column, "/");
        }
    }
    else if (c == '(')
    {
        t = Token(L_BRACK, current_line, current_column, "(");
    }
    /*
    else if (c == '~')
    {
        t = Token(NEGATION, current_line, current_column, "~");
    }
    */
    else if (c == ')')
    {
        t = Token(R_BRAK, current_line, current_column, ")");
    }
    else if (c == '{')
    {
        t = Token(L_BRACE, current_line, current_column, "{");
    }
    else if (c == '}')
    {
        t = Token(R_BRACE, current_line, current_column, "}");
    }

    else if (c == '[')
    {

        t = Token(L_PAREN, current_line, current_column, "[");
    }
    else if (c == ']')
    {
        t = Token(R_PAREN, current_line, current_column, "]");
    }
    else if (c == '?')
    {
        t = Token(CHECK, current_line, current_column, "?");
    }
    //comparators
    else if (c == '>')
    {
        if (input_stream.peek() != '=')
            t = Token(GREATER_THAN, current_line, current_column, ">");
        else
        {
            t = Token(GREATER_THAN_EQ, current_line, current_column, ">=");
            input_stream.get();
        }
    }
    else if (c == '=')
    {
        if (input_stream.peek() != '=')
            t = Token(COMPARE, current_line, current_column, "=");
        else
        {
            t = Token(COMPARE, current_line, current_column, "=");
            input_stream.get();
            current_column++;
        }
    }

    else if (c == ':')
    {
        if (input_stream.peek() != ':')
        {

            t = Token(ASSIGNMENT, current_line, current_column, ":");
        }
        else
        {
            t = Token(EXTENDS, current_line, current_column, "extends");
            input_stream.get();
            current_column++;
        }
    }
    else if (c == '!')
    {
        if (input_stream.peek() != '=')
            t = Token(NOT, current_line, current_column, "!");
        else
        {
            t = Token(NOT_EQUAL, current_line, current_column, "!=");
            input_stream.get();
            current_column++;
        }
    }
    else if (c == '<')
    {
        if (input_stream.peek() != '=')
        {
            c = input_stream.get();
            /*            if (c == '>')
            {
                t = Token(EQUIVALANCE, current_line, current_column, "<=>");
            }
            else
            {
                t = Token(LESS_THAN, current_line, current_column, "<");
            }
*/
            t = Token(LESS_THAN, current_line, current_column, "<");
        }
        else
        {
            t = Token(LESS_THAN_EQ, current_line, current_column, "<=");
            input_stream.get();
            current_column++;
        }
    }
    /*
    else if (c == '\\')
    {
        if (input_stream.peek() == '=')
        {
            t = Token(BACKSLASH_LESS_THAN_EQ, current_line, current_column, "");
            input_stream.get();
            current_column++;
        }
        else if (input_stream.peek() == ';')
        {
            t = Token(BACKSLASH_SEMICOLON, current_line, current_column, "");
            input_stream.get();
            current_column++;
        }
        else if (input_stream.peek() == '(')
        {
            t = Token(BACKSLASH_L_BRACK, current_line, current_column, "");
        }
        else if (input_stream.peek() == ')')
        {
            t = Token(BACKSLASH_R_BRAK, current_line, current_column, "");
        }
        else if (input_stream.peek() == '{')
        {
            t = Token(BACKSLASH_L_BRACE, current_line, current_column, "");
        }
        else if (input_stream.peek() == '}')
        {
            t = Token(BACKSLASH_R_BRACE, current_line, current_column, "");
        }

        else if (input_stream.peek() == '[')
        {

            t = Token(BACKSLASH_L_PAREN, current_line, current_column, "");
        }
        else if (input_stream.peek() == ']')
        {
            t = Token(BACKSLASH_R_PAREN, current_line, current_column, "");
        }
        else if (input_stream.peek() == '?')
        {
            t = Token(BACKSLASH_CHECK, current_line, current_column, "");
        }
        //comparators
        else if (input_stream.peek() == '>')
        {
            c = input_stream.get();
            if (c != '=')
                t = Token(BACKSLASH_GREATER_THAN, current_line, current_column, "");
            else
            {
                t = Token(BACKSLASH_GREATER_THAN_EQ, current_line, current_column, "");
                input_stream.get();
            }
        }
        else if (input_stream.peek() == '=')
        {
            c = input_stream.get();
            if (c != '=')
                t = Token(BACKSLASH_COMPARE, current_line, current_column, "");
            else
            {
                t = Token(BACKSLASH_COMPARE, current_line, current_column, "");
                input_stream.get();
                current_column++;
            }
        }

        else if (input_stream.peek() == ':')
        {
            c = input_stream.get();
            if (c != ':')
            {

                t = Token(BACKSLASH_ASSIGNMENT, current_line, current_column, "");
            }
            else
            {
                t = Token(BACKSLASH_EXTENDS, current_line, current_column, "");
                input_stream.get();
                current_column++;
            }
        }
        else if (input_stream.peek() == '!')
        {
            c = input_stream.get();
            if (c != '=')
                t = Token(BACKSLASH_NOT, current_line, current_column, "");
            else
            {
                t = Token(BACKSLASH_NOT_EQUAL, current_line, current_column, "");
                input_stream.get();
                current_column++;
            }
        }
        else if (input_stream.peek() == '<')
        {
            c = input_stream.get();
            if (c != '=')
                t = Token(BACKSLASH_LESS_THAN, current_line, current_column, "");
            else
            {
                t = Token(LESS_THAN_EQ, current_line, current_column, "");
                input_stream.get();
                current_column++;
            }
        }
        else if (input_stream.peek() == '\\')
        {
            t = Token(BACKSLASH_BACKSLASH, current_line, current_column, "");
            input_stream.get();
            current_column++;
        }
        else
        {
            t = Token(BACKSLASH, current_line, current_column, "");
        }
    }
    */
    //identifiers
    else if (isalpha(c) || c == '_' || input_stream.peek() == '_')
    {
        std::string theStr = "";
        theStr += c;
        int startColumn = current_column;
        bool getString = true;
        //make string until whitespace or any other symbol
        while (getString)
        {
            if (isalpha(input_stream.peek()) || isdigit(input_stream.peek()) || input_stream.peek() == '_')
            {
                c = getNextChar();
                theStr += c;
            }
            else
                getString = false;
        }
        //possible reserved words
        if (theStr == "and")
        {
            t = Token(AND, current_line, startColumn, theStr);
        }
        else if (theStr == "as")
        {
            t = Token(AS, current_line, startColumn, theStr);
        }
        else if (theStr == "new")
        {
            t = Token(NEW, current_line, startColumn, theStr);
        }
        else if (theStr == "or")
        {
            t = Token(OR, current_line, startColumn, theStr);
        }
        else if (theStr == "out")
        {
            t = Token(OUT, current_line, startColumn, theStr);
        }
        else if (theStr == "using")
        {
            t = Token(USING, current_line, startColumn, theStr);
        }
        /*else if (theStr == "loop")
		{
			t = Token(LOOP, current_line, startColumn, theStr);
		}
		*/
        else if (theStr == "in")
        {
            t = Token(IN, current_line, startColumn, theStr);
        }
        else if (theStr == "serve")
        {
            t = Token(SERVE, current_line, startColumn, theStr);
        }
        else if (theStr == "self")
        {
            t = Token(SELF, current_line, startColumn, theStr);
        }
        else if (theStr == "return")
        {
            t = Token(RETURN, current_line, startColumn, theStr);
        }
        else if (theStr == "true")
        {
            t = Token(BOOL_TRUE, current_line, startColumn, theStr);
        }
        else if (theStr == "false")
        {
            t = Token(BOOL_FALSE, current_line, startColumn, theStr);
        }
        /*
        else if (theStr == "namespace")
        {
            t = Token(NAMESPACE, current_line, startColumn, theStr);
        }
        */
        else if (theStr == "not")
        {
            t = Token(NOT, current_line, startColumn, theStr);
        }
        else if (theStr == "_string_")
        {
            t = Token(TYPE_STRING, current_line, startColumn, "");
        }

        else if (theStr == "_int_")
        {
            t = Token(TYPE_INT, current_line, startColumn, "");
        }
        else if (theStr == "_float_")
        {
            t = Token(TYPE_FLOAT, current_line, startColumn, "");
        }
        else if (theStr == "_bool_")
        {
            t = Token(TYPE_BOOL, current_line, startColumn, "");
        }
        else if (theStr == "_void_")
        {
            t = Token(TYPE_VOID, current_line, startColumn, "");
        }
        else if (theStr == "_const_")
        {
            t = Token(TYPE_CONST, current_line, startColumn, "");
        }
        else if (theStr == "_private_")
        {
            t = Token(PRIVATE, current_line, startColumn, "");
        }
        else if (theStr == "if")
        {
            t = Token(IF, current_line, startColumn, theStr);
        }
        else if (theStr == "else")
        {
            t = Token(ELSE, current_line, startColumn, theStr);
        }
        else if (theStr == "while")
        {
            t = Token(WHILE, current_line, startColumn, theStr);
        }
        else if (theStr == "file")
        {
            t = Token(T_FILE, current_line, startColumn, theStr);
        }
        else if (theStr == "driver")
        {
            t = Token(DRIVER, current_line, startColumn, theStr);
        }

        else if (theStr == "_method_")
        {
            t = Token(TYPE_METHOD, current_line, startColumn, "");
        }
        /*
        else if (theStr == "_child_")
        {
            t = Token(CHILD, current_line, startColumn, theStr);
        }
        */
        else if (theStr == "call")
        {
            t = Token(CALL, current_line, startColumn, theStr);
        }
        else
        {
            return Token(ID, current_line, current_column, theStr);
        }
    }

    //string type
    else if (c == '"')
    {
        std::string theStr = "";
        int firstLetterColumn = current_column;
        c = getNextChar();
        //make string until another double quotation
        while (c != '"' || c == '\n')
        {
            theStr += c;
            c = input_stream.get();
            current_column++;
            if (c == '\n')
            {
                current_line++;
                throw ReadingError("string should be inline in this update of vip.");
                cerr << "wrong string type " << current_line << ", coloumn :" << current_column << endl;
                return Token(ID, current_line, firstLetterColumn, "String Error");
            }
        }
        t = Token(STRING_TYPE, current_line, firstLetterColumn, theStr);
    }
    //number type
    else if (isdigit(c))
    {
        std::string theNumber = "";
        theNumber += c;
        bool hasDecimal = false;
        int firstLetterColumn = current_column;
        while (isdigit(input_stream.peek()) || input_stream.peek() == '.')
        {
            c = getNextChar();
            //block ensures only one decimal point or
            //Token type returned is ERROR
            if (c == '.')
            {
                if (!hasDecimal)
                {
                    theNumber += c;
                    hasDecimal = true;
                }
                else
                {
                    //returns error if more than one decimal point
                    cout << "Error in line: " << current_line << "in column: " << current_column;
                    throw ReadingError("Invalid Decimal Number");
                    return Token(ERROR, current_line, firstLetterColumn, "Invalid Decimal Number");
                }
            }
            else
            {
                theNumber += c;
            }
        }
        //return correct type FLOAT_TYPE or INT_TYPE
        t = (hasDecimal) ? Token(FLOAT_TYPE, current_line, firstLetterColumn, theNumber) : Token(INT_TYPE, current_line, firstLetterColumn, theNumber);
    }
    //end of stream token
    else if (input_stream.eof())
    {
        t = Token(EOP, current_line, current_column, "EOP");
    }
    //ERROR Token
    else
    {
        std::string lex = "";
        lex += c;
        t = Token(ERROR, current_line, current_column, lex);
    }
    return t;
}
char Lexer::getNextChar()
{
    char c = input_stream.get();
    current_column++;
    while (c == '\n')
    {
        current_line++;
        current_column = 0;
        c = input_stream.get();
    }
    return c;
}