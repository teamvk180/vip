#include "interpreter.h"
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

interpreter::interpreter(int argc,char **argv)
{
     ifstream fin;
    vector<string> filenames;
    for (int i = 1; i < argc; i++)
    {
        fin.open(argv[i]);
        if (fin.fail())
        {
            cerr << "file '" << argv[i] << "' not exist!";
            exit(-1);
        }
        filenames.push_back(argv[i]);
        fin.close();
    }
    
    Parser the_parser = Parser(filenames);
    if (!the_parser.HasError)
    {
        cout <<"evaluvating"<<endl;
        vector<Expression *> ast = the_parser.getSyntaxTree();
        for (const auto p : ast)
        {
             p->evaluvate();
        }
    }
}

interpreter::~interpreter()
{
}