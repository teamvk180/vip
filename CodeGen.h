#ifndef _CODE_GEN_H
#define _CODE_GEN_H
#include "Token.h"
#include "generator.h"
#include <string>
#include <ios>
#include <io.h>
#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <ostream>
using namespace std;
//#define fout cout
template <typename T>
std::string ToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}
using namespace std;
const std::string isEnd = "\n";
class CodeGen
{
private:
    string _method_name_;
    int ifLabelCount;
    int whileLabelCount;
    //ofstream fout;
    bool isMethod;
    std::string head;
    std::string body;
    std::string main;

public:
    CodeGen()
    {
        ifLabelCount = 0;
        whileLabelCount = 0;
    };
    gen outfile;
    std::string encode_to_unicode(char a);
    //symbol_tab mTab;
    void writeMethodDecl(int index, std::string input);
    void writeParams(std::string input);
    void writeDriver_call(std::string msg);
    void setup_python(std::string input);
    void write_method_decl(std::string msg);
    void write_method_call(std::string msg);
    //GEN types.
    void emit(std::string data_r)
    {
    }
    // Usage example: filePutContents("./yourfile.txt", "content", true);
    void fill_contents(std::string name, const std::string content, bool append);
    void clearfile(const std::string file_name);
    std::string removeDup(string str);
    void write(int destination, std::string data);
    const std::string get_body() { return this->body; }
    const std::string get_main() { return this->main; }
    const std::string get_header() { return this->head; }
};
#endif
