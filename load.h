#ifndef LOADER_H
#define LOADER_H
#include <vector>
#include "Token.h"
#include <iostream>
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

} container_source;
typedef struct
{
    std::string var_name;
    //member var for line
    int var_type;
} var_t;
class loader
{
public:
    std::vector<container_source> source;
    std::vector<container_source> give_load();
    int get_size()
    {
        return source.size();
    }

    std::string file_name();
    Token get_token();
    void show_buff();
    void update_buffer()
    {
        this->read++;
    }
    void outdate_buffer()
    {
        if (read == 0)
        {
            return;
        }
        this->read--;
    }

    Token next();
    Token previous();
    int current_read_position();
    bool atEnd();
    void reset(int position);

private:
    size_t read = 0;
    size_t next_read = 0;
    size_t previous_read = 0;
};
#endif