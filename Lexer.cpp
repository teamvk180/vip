#include "Lexer.h"
#include "Exception.h"
#include "Token.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
void Lexer::resetRow()
{
    current_line = 0;
    current_coloumn = 0;
}

vector<std::string> Lexer::lexStdFunc()
{

    std::ifstream ifs("./conf/vipStdFunc.vp");
    if (ifs.fail())
    {
        cerr << "vip config file missing " << endl;
    }
    std::string el;
    vector<std::string> d;
    while (getline(ifs, el, '\n'))
    {
        cout << "line : " << el << endl;
        d.push_back(el);
    }
    return d;
}

void Lexer::openFile(const string &filename)
{
    current_line, current_coloumn = 0;
    cout << "file : " << filename << endl;
    string suffix = filename.substr(filename.size() - 3, filename.size());
    if (suffix != ".vp")
    {
        cerr << "file '" << filename
             << "' is not a standard vip-- file, filename must be ended by '.vp' "
             << endl;
        exit(-1);
    }
    input_stream.open(filename);
    if (input_stream.fail())
    {
        cerr << "file " << filename << " does not exit" << endl;
        exit(-1);
    }
}

void Lexer::closeFile() { input_stream.close(); }

char Lexer::read()
{
    char c = input_stream.get();
    current_coloumn++;
    if (c == '\n')
    {
        current_line++;
        current_coloumn = 0;
    }
    return c;
}

Token Lexer::nextToken()
{
    char c = read();
    Token t;
    std::string kstring;
    kstring = c;
    //if whitespace; get next char until not whitespace

    while (isspace(c) || c == '\n' || c == '\t')
    {
        c = read();
    }

    if (c == '/' && input_stream.peek() == '/')
    {
        while (input_stream.peek() != '\n')
        {
            c = read();
        }
        return nextToken();
    }

    if (c == ';')
    {
        t = Token(type::SEMICOLON, current_line, current_coloumn, ";");
    }
    else if (c == ',')
    {
        t = Token(type::COMMA, current_line, current_coloumn, ",");
    }

    else if (c == '@')
    {
        c = read();
        //string type
        if (c == '"')
        {
            std::string theStr = "";
            int firstLetterColumn;
            c = read();
            //make string until another double quotation
            while (c != '"')
            {
                theStr += c;
                c = read();
            }
            t = Token(type::LINK, current_line, firstLetterColumn, theStr);
        }
        else
        {
            std::string theStr = "";
            theStr += c;
            int startColumn = current_coloumn;
            bool getString = true;
            //make string until whitespace or any other symbol
            while (getString)
            {
                if ((isalpha(input_stream.peek()) || isdigit(input_stream.peek())) && !isspace(input_stream.peek()))
                {
                    c = read();
                    theStr += c;
                    if (c == '\n')
                    {
                        cerr << " an @overrider should be inline " << endl;
                        break;
                    }
                }
                else
                    getString = false;
            }
            if (theStr.empty())
            {
                cerr << "error on @overrider" << endl;
            }
            else
            {
                t = Token(type::OVERRIDE, current_line, current_coloumn, theStr);
            }
        }
    }
    else if (c == '.')
    {

        if (input_stream.peek() == '.')
        {
            c = read();
            if (c != '.')
            {
                cerr << "expected a ... but .. is only lexed" << endl;
            }
            t = Token(type::DOUBLE_POINT, current_line, current_coloumn, "...");
            read();
        }
        else
            t = Token(type::DOT, current_line, current_coloumn, ".");
    }
    else if (c == '/')
    {
        if (input_stream.peek() == '*')
        {
            //cout << "comment found" << endl;
            c = read();
            //make comment until another */
            while (true)
            {
                if (c == '*')
                {
                    c = read();
                    if (c == '/')
                    {
                        break;
                    }
                    current_coloumn++;
                }
                else
                {
                    c = read();
                }
            }
            read();
            current_coloumn++;
            return nextToken();
        }
    }
    else if (c == '(')
    {
        t = Token(type::LPAR, current_line, current_coloumn, "(");
    }
    else if (c == '~')
    {
        t = Token(type::NOT, current_line, current_coloumn, "~");
    }
    else if (c == ')')
    {
        t = Token(type::RPAR, current_line, current_coloumn, ")");
    }
    else if (c == '{')
    {
        t = Token(type::LBRACE, current_line, current_coloumn, "{");
    }
    else if (c == '}')
    {
        t = Token(type::RBRACE, current_line, current_coloumn, "}");
    }

    else if (c == '[')
    {

        t = Token(type::L_SQ_BRACE, current_line, current_coloumn, "[");
    }
    else if (c == ']')
    {
        t = Token(type::R_SQ_BRACE, current_line, current_coloumn, "]");
    }
    //comparators

    else if (c == ':')
    {
        if (input_stream.peek() != ':')
        {

            t = Token(type::ASSIGN, current_line, current_coloumn, ":");
        }
        else
        {
            t = Token(type::MEMBEROF, current_line, current_coloumn, "memberof");
            read();
            current_coloumn++;
        }
    }
    //number type
    else if (isdigit(c))
    {
        std::string theNumber = "";
        theNumber += c;
        bool hasDecimal = false;
        int firstLetterColumn;
        while (isdigit(input_stream.peek()) || input_stream.peek() == '.')
        {
            c = read();
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
                    cout << "Error in line: " << current_line << "in column: " << current_coloumn << endl;
                    cerr << "Invalid Decimal Number";
                    return Token(type::ERROR, current_line, firstLetterColumn, "Invalid Decimal Number");
                }
            }
            else
            {
                theNumber += c;
            }
        }
        //return correct type FLOAT_TYPE or INT_TYPE
        t = (hasDecimal) ? Token(type::FLOAT, current_line, firstLetterColumn, theNumber) : Token(type::INT, current_line, firstLetterColumn, theNumber);
    }
    else if (isalpha(c) || c == '_' || input_stream.peek() == '.' || input_stream.peek() == '_' || input_stream.peek() == '-')
    {
        std::string theStr = "";
        theStr += c;
        int startColumn = current_coloumn;
        bool getString = true;
        //make string until whitespace or any other symbol
        while (getString)
        {
            if (isalpha(input_stream.peek()) ||
             isdigit(input_stream.peek()) || 
             input_stream.peek() == '_' ||
             input_stream.peek() == '-' || 
             input_stream.peek() == '.')
            {
                c = read();
                theStr += c;
            }
            else
                getString = false;
        }
        //possible reserved words
        if (theStr == "and")
        {
            t = Token(type::AND, current_line, startColumn, theStr);
        }
        else if (theStr == "as")
        {
            t = Token(type::AS, current_line, startColumn, theStr);
        }
        else if (theStr == "using")
        {
            t = Token(type::USING, current_line, startColumn, theStr);
        }
        else if (theStr == "or")
        {
            t = Token(type::OR, current_line, startColumn, theStr);
        }

        else if (theStr == "use")
        {
            t = Token(type::USE, current_line, startColumn, theStr);
        }
        else if (theStr == "provide")
        {
            t = Token(type::PROVIDE, current_line, startColumn, theStr);
        }

        else if (theStr == "extends")
        {
            t = Token(type::EXTENDS, current_line, startColumn, theStr);
        }
        else if (theStr == "enum")
        {
            t = Token(type::ENUM, current_line, startColumn, theStr);
        }
        else if (theStr == "self")
        {
            t = Token(type::SELF, current_line, startColumn, theStr);
        }
        else if (theStr == "return")
        {
            t = Token(type::RETURN, current_line, startColumn, theStr);
        }
        else if (theStr == "true")
        {
            t = Token(type::TRUE, current_line, startColumn, theStr);
        }
        else if (theStr == "false")
        {
            t = Token(type::FALSE, current_line, startColumn, theStr);
        }
        else if (theStr == "not")
        {
            t = Token(type::NOT, current_line, startColumn, theStr);
        }
        else if (theStr == "assign")
        {
            t = Token(type::ASSIGN, current_line, startColumn, theStr);
        }
        else if (theStr == "to")
        {
            t = Token(type::TO, current_line, startColumn, theStr);
        }
        else if (theStr == "then")
        {
            t = Token(type::THEN, current_line, startColumn, theStr);
        }        
        else if (theStr == "string")
        {
            t = Token(type::STRING_CAST, current_line, startColumn, theStr);
        }

        else if (theStr == "int")
        {
            t = Token(type::INT_CAST, current_line, startColumn, theStr);
        }
        else if (theStr == "float")
        {
            t = Token(type::FLOAT_CAST, current_line, startColumn, theStr);
        }
        else if (theStr == "bool")
        {
            t = Token(type::BOOL_CAST, current_line, startColumn, theStr);
        }
        else if (theStr == "void")
        {
            t = Token(type::VOID, current_line, startColumn, theStr);
        }
        else if (theStr == "equals")
        {
            t = Token(type::EQUALS, current_line, startColumn, theStr);
        }
        else if (theStr == "class")
        {
            t = Token(type::CLASS, current_line, startColumn, theStr);
        }
        else if (theStr == "field")
        {
            t = Token(type::FIELD, current_line, startColumn, theStr);
        }
        else if (theStr == "static")
        {
            t = Token(type::STATIC, current_line, startColumn, theStr);
        }
        else if (theStr == "method")
        {
            t = Token(type::METHOD, current_line, startColumn, theStr);
        }
        else if (theStr == "if")
        {
            t = Token(type::IF, current_line, startColumn, theStr);
        }
        else if (theStr == "else")
        {
            t = Token(type::ELSE, current_line, startColumn, theStr);
        }
        else if (theStr == "while")
        {
            t = Token(type::WHILE, current_line, startColumn, theStr);
        }
        else if (theStr == "foreach")
        {
            t = Token(type::FOR_EACH, current_line, startColumn, theStr);
        }
        else if (theStr == "child")
        {
            t = Token(type::CHILD, current_line, startColumn, theStr);
        }
        else if (theStr == "function")
        {
            t = Token(type::FUNCTION, current_line, startColumn, theStr);
        }
        else if (theStr == "create-instance")
        {
            t = Token(type::CREATE_INSTANCE, current_line, startColumn, theStr);
        }
        else if (theStr == "call")
        {
            t = Token(type::CALL, current_line, startColumn, theStr);
        }
        else
        {
            return Token(type::IDENTIFIER, current_line, current_coloumn, theStr);
        }
    }

    //string type
    else if (c == '"')
    {
        std::string theStr = "";
        int firstLetterColumn;
        c = read();
        //make string until another double quotation
        while (c != '"')
        {
            theStr += c;
            c = read();
        }
        t = Token(type::STRING, current_line, firstLetterColumn, theStr);
    }
    else if (c == '\'')
    {
        std::string theStr = "";
        int firstLetterColumn;
        c = read();
        //make string until another double quotation
        while (c != '\'')
        {
            theStr += c;
            c = read();
        }
        t = Token(type::STRING, current_line, firstLetterColumn, theStr);
    }

    //end of stream token
    else if (c == EOF || input_stream.peek() == EOF)
    {
        t = Token(type::EOS, current_line, current_coloumn, "EOS");
    }
    else if (input_stream.fail())
    {
        throw "unable to read from input file";
        exit(0);
    }
    //ERROR Token
    else
    {
        std::string lex = "";
        lex += c;
        t = Token(type::ERROR, current_line, current_coloumn, lex);
    }
    return t;
}