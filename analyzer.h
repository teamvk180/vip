#ifndef _ANALYZER_H
#define _ANALYZER_H
#include "SymbolTable.h"
#include <vector>
#include "Token.h"
#include <iterator>
//#define fout cout
/*
template <typename T>
std::string ToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}
*/

class Analyzer
{
private:
    /*
    void analyzeIF();
    void evaluvate_expression(int label, vector<Token> tok, std::string mData);
    void evaluvate_statements(int label, vector<Token> tok, std::string mData);
    void set_tree(tree_cache ast) { ast_ = ast; }
    void eval_serve(std::string mDat, vector<Token> token);
    void eval_driver_call(std::string mDat, vector<Token> token);
    void eval_identifier(std::string mDat, vector<Token> token);
    void eval_method_call(std::string mDat, vector<Token> token);
    void eval_method_decl(std::string mDat, vector<Token> token);
    void eval_return(std::string mDat, vector<Token> token);
    void evaluvate_statement(Token t);
   */
public:
    void analyze_variable(Token t);
    size_t std_driver = 0;
    int plece_give_me_an_id()
    {
        jackki_patti_pettu++;
        return jackki_patti_pettu;
    };
    vector<std::string> driver_link;
    bool cli_display_driver = false;
    bool cli_input_driver = false;
    bool driver_call_driver = false;
    bool py_driver = false;
    bool add_driver = false;
    bool sub_driver = false;
    bool mul_driver = false;
    bool div_driver = false;
    bool lte_driver = false;
    bool gte_driver = false;
    bool lt_driver = false;
    bool gt_driver = false;
    void set_link(std::string link_name, bool driver_id)
    {
        if (driver_id)
            return;
        else
            driver_link.push_back(link_name);
        return;
    }
    size_t current_read = 0;
    size_t jackki_patti_pettu = 1;
};

#endif
