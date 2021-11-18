/* Main file to test class parse
 */
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Exception.h"
#include <ostream>
#include "interpreter.h"
#include "Lexer.h"
#include <stdio.h>
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

//tcc_make_black_forest_for_vip(int argc, char **argv)
Flags getFlags(int argc, char **argv);

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
        cout << "vip v" << 20 << "." << 0 << "." << 1 << "." << endl;
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
        cout << "vip version " << 20 << "." << 0 << "." << 1 << endl;
        return 0;
    }

    if (flags.inFiles.empty())
    {
        cout << "no source file specified" << endl;
        cout << "try 'vip -h' for help" << endl;
        return 0;
    }

    /*    for (size_t i = 0; i < flags.inFiles.size(); i++)
    {

        cout << flags.inFiles[i] << endl;
        std::string f(flags.inFiles[i]);
        Lexer the_lexer;
        the_lexer.openFile(f);
        Token t;
        while (t.token_type != type::EOS)
        {
            t = the_lexer.nextToken();
            cout << (int)t.token_type << "\t" << t.lexeme << endl;
        }
        the_lexer.closeFile();

        // Parser the_parser = Parser(the_lexer);
    }
*/
       interpreter *inter = new interpreter(argc,argv);

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
