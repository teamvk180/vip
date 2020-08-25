/* Main file to test class parse
 */
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "load.h"
#include <ostream>
#include "parser.h"
#include "Lexer.h"
#include <stdio.h>
#include "patch.h"
#include "analyzer.h"
#include "CodeGen.h"
#include <cstdlib>
#include <algorithm>
using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> cmdLineArgs;
struct Flags
{
    vector<string> inFiles; // all the input files
    bool debug = false;     // if to show debugging info
    bool help = false;      // if to show help message
    bool version = false;   // if to show version message
    bool flagError = false; // if to quit immediately, this is set if there is an unrecognised flag
};
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}
bool load_header()
{
    //__internal__std_lib_do_not_Delete
    loader load;
    //gen code_;
    int line = 0, column = 0;
    std::ifstream infile("__internal__std_lib_do_not_Delete/*.vipx");
    Lexer the_lexer(infile);
    while (!infile.eof() || !infile.fail())
    {
        Token output = the_lexer.next_token();
        container_source in;
        in.file_name = "__VIP_STD_ENGINE__";
        in.token_type = (int)output.type();
        in.token_line = (int)output.line();
        line = in.token_line;
        in.token_column = (int)output.column();
        column = in.token_column;
        in.token_lexeme = (string)output.lexeme();
        // cout << in.token_type << "\t" << in.token_line << "\t" << in.token_column << "\t" << in.token_lexeme << endl;
        load.source.push_back(in);
    }
    container_source large;
    large.token_type = EOH;
    large.token_line = line;
    large.token_column = column;
    large.token_lexeme = "EOH";
    load.source.push_back(large);
    load.show_buff();
    return true;
}
//tcc_make_black_forest_for_vip(int argc, char **argv)
Flags getFlags(int argc, char **argv);
int make_heap_of_pages(std::string file_name)
{
}
int main(int argc, char **argv)
{
    Flags flags = getFlags(argc, argv);

    if (flags.flagError)
    {
        cout << "try 'vip -h' for help" << endl;
        return 0;
    }

    if (flags.help)
    {
        cout << "-----------------------------------" << endl;
        cout << "\n\a\b\t"
             << "'Visual Interface Programming'" << endl;
        cout << "vip v" << 20 << "." << 0 << "." << 0 << "." << endl;
        cout << "usage: vip [options] [source file] " << endl;
        cout << "options: " << endl;
        cout << "-a -about           display about vip programming language" << endl;
        cout << "-l -licence         display the licence of vip programming language" << endl;
        cout << "-v, -version        display the version of vip" << endl;
        cout << "-d, -debug          display debugging info before running the program" << endl;
        cout << "                    active by default if no transpiling commands are present" << endl;
        cout << "                    currently, anything after -r is ignored" << endl;
        cout << "-h, -help           display this help and quit" << endl;
        cout << endl;
        cout << endl;

        return 0;
    }

    if (flags.version)
    {
        cout << "vip version " << 20 << "." << 0 << "." << 0 << endl;
        return 0;
    }

    if (flags.inFiles.empty())
    {
        cout << "no source file specified" << endl;
        cout << "try 'vip -h' for help" << endl;
        return 0;
    }
    /*  else if (flags.inFiles.size() > 1)
    {
    }

    int line = 0, column = 0;
    loader load;
    for (size_t i = 0; i <= flags.inFiles.size(); i++)
    {

        std::cout << "initializied .." << std::endl;
        cout << "infile " << flags.inFiles[i] << endl;
        std::ifstream infile(flags.inFiles[i]);
        Lexer the_lexer(infile);
        while (!infile.eof())
        {
            Token output = the_lexer.next_token();
            container_source in;
            in.file_name = flags.inFiles[i];
            in.token_type = (int)output.type();
            in.token_line = (int)output.line();
            line = in.token_line;
            in.token_column = (int)output.column();
            column = in.token_column;
            in.token_lexeme = (string)output.lexeme();
            //cout << in.token_type << "\t" << in.token_line << "\t" << in.token_column << "\t" << in.token_lexeme << endl;
            load.source.push_back(in);
        }
    }
    //load.create_var_tab();
    load.show_buff();
    container_source large;
    large.token_type = EOS;
    large.token_line = 0xffff;
    large.token_column = 0xffff;
    large.token_lexeme = "EOF";
    load.source.push_back(large);
    Parser the_parser = Parser(load);
    Ast *the_tree = the_parser.Parse();
    */
    loader load;
    container_source in;
    //gen code_;
    int line = 0, column = 0;
    for (size_t i = 0; i < flags.inFiles.size(); i++)
    {

        cout << flags.inFiles[i] << endl;
        std::ifstream infile(flags.inFiles[i].c_str());
        Lexer the_lexer(infile);
        while (!infile.eof() || !infile.fail())
        {
            Token output = the_lexer.next_token();
            in.file_name = flags.inFiles[i];
            in.token_type = (int)output.type();
            in.token_line = (int)output.line();
            line = in.token_line;
            in.token_column = (int)output.column();
            column = in.token_column;
            in.token_lexeme = (string)output.lexeme();
            // cout << in.token_type << "\t" << in.token_line << "\t" << in.token_column << "\t" << in.token_lexeme << endl;
            load.source.push_back(in);
        }
    }
    //load.create_var_tab();
    //code the_code;
    in.token_type = EOS;
    in.token_line = line;
    in.token_column = column;
    in.token_lexeme = "EOF";
    load.source.push_back(in);
#ifdef DEBUG
    load.show_buff();
#endif
    std::string code = "";
    Parser the_parser = Parser(load);
    std::string cur_dir(argv[0]);
    int pos = cur_dir.find_last_of("/\\");
    std::string path = "g++ ";
    path += cur_dir.substr(0, pos);
    path += "\\temp\\in.cpp ";
    //path += the_parser.link;
    std::string temp_link = " " + cur_dir.substr(0, pos) + "\\driver\\*.o";
    path += temp_link + "  -o a.exe -std=c++11 -lstdc++";
    const char *_jok_k_code = path.data();
    printf("kcatc:%s\n", _jok_k_code);
    //std::cout << "path: " << cur_dir.substr(0, pos) << std::endl;
    //std::cout << "file: " << cur_dir.substr(pos + 1) << std::endl;
    system(_jok_k_code);
    cout << " writing perfect " << endl;
    return 0;
}

Flags getFlags(int argc, char **argv)
{
    bool after = false;
    Flags flags;

    for (int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        if (!after)
        {
            if (arg.size() > 1 && arg[0] == '-')
            {
                string flag = arg.substr(1, string::npos);

                if (flag == "d" || flag == "debug")
                {
                    flags.debug = true;
                }
                else if (flag == "v" || flag == "version")
                {
                    flags.version = true;
                }
                else if (flag == "h" || flag == "help")
                {
                    flags.help = true;
                }
                else if (flag == "a" || flag == "about")
                {
                    cout << "                         -----------VIRTUAL INTELLIGENT PROGRAMMING LANGUAGE--------------                     " << endl;
                    cout << "IT IS A GENERAL PURPOSE PROGRAMMING LANGUAGE. IT IS DEVELOPED BY VISHAL KRISHNA AG & VIVEK KRISHNA AG , THIS PROGRAMMING LANGUAGE SUPPORTS GARBAGE COLLECTION AT RUN TIME " << endl;
                    cout << "THIS LANGUAGE IS HARD CODED ,THE CONCEPTS THAT ARE USED IN THIS IS LIABLES FOR VISHAL KRISHNA AG , THE SOFTWARE IS PROVIDED AS IS , WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING " << endl;
                    cout << "BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. THIS SOFTWARE IS NOT USED FOR ILLEGAL ACTIVITYS" << endl;
                    cout << "IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, " << endl;
                    cout << "WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE." << endl;
                }
                else if (flag == "l" || flag == "licence")
                {
                    cout << "LICENCE Is not allocated now" << endl;
                }
                else
                {
                    cout << "unknown Argument '" + flag + "' is not supported in vip ;" << endl;
                    //flags.flagError = true;
                    after = true;
                }
            }
            else
            {
                flags.inFiles.push_back(arg);
                cmdLineArgs.push_back(arg);
            }
        }
        else
        {
            cmdLineArgs.push_back(arg);
        }
    }

    return flags;
}
