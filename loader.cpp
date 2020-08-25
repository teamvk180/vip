#include "load.h"
#include "Exception.h"
Token loader::get_token()
{
    Token tok;
    tok.setType(source.at(read).token_type);
    tok.setLine(source.at(read).token_line);
    tok.setColumn(source.at(read).token_column);
    tok.setLexeme(source.at(read).token_lexeme);
    //read = read + 1;
    //std::cout << "reading count <<" << read << std::endl;
    return tok;
}
int loader::current_read_position()
{
    return this->read;
}
bool loader::atEnd()
{
    if (source.at(read).token_type == EOP)
    {
        return true;
    }
    return false;
}
void loader::reset(int position)
{
    this->read = position;
}

std::vector<container_source> loader::give_load()
{
    std::vector<container_source> _m_new_source(source);
    return _m_new_source;
}

void loader::show_buff()
{
    for (size_t i = 0; i < source.size(); i++)
    {
        std::cout << i << "\t" << source[i].token_type << "\t" << source[i].token_line << "\t" << source[i].token_column << "\t" << source[i].token_lexeme << std::endl;
        if (source[i].token_type == EOS)
        {
            std::cout << "reading completed " << std::endl;
            break;
        }
    }
}
std::string loader::file_name()
{
    return source.at(read).file_name;
}

Token loader::next()
{
    Token next_token;
    next_read = read + 1;
    next_token.setType(source.at(next_read).token_type);
    next_token.setLine(source.at(next_read).token_line);
    next_token.setColumn(source.at(next_read).token_column);
    next_token.setLexeme(source.at(next_read).token_lexeme);
    next_read = 0;
    return next_token;
}
Token loader::previous()
{
    Token previous_token;
    previous_read = read - 1;
    previous_token.setType(source.at(previous_read).token_type);
    previous_token.setLine(source.at(previous_read).token_line);
    previous_token.setColumn(source.at(previous_read).token_column);
    previous_token.setLexeme(source.at(previous_read).token_lexeme);
    previous_read = 0;
    return previous_token;
}