#include "CodeGen.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <istream>
#include "Token.h"
#include <sstream>
using namespace std;

/*
 set_id(for client can be dynamic now static ip);
set_self_stack(); //of vip driver is the vertual implementation of vip 
                //piller methods used make vip go forward.
set_src(NOT_REQUIRED);
set_dst(DESTINATION_ROUTER_STATIC_IP);
//set_service();
go();
 */

std::string pydriver_caller_unit(std::string input)
{
    ifstream f(input); //taking file as inputstream
    string str;
    if (f)
    {
        if (f.fail())
        {
            cout << input + "file not found" << endl;
        }
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    return str;
}
void CodeGen::setup_python(std::string input)
{
    this->emit("eval_py(\"" + input + "\");\n");

    return;
}
std::string CodeGen::encode_to_unicode(char a)
{
    //now for the sake of simplicity we convert to ascii
    return ToString(int(a));
}

void CodeGen::write_method_decl(std::string msg)
{
    this->emit("vip_decl_method();" + isEnd);
}
void CodeGen::write_method_call(std::string msg)
{
    this->emit("vip_method_call();" + isEnd);
}

void CodeGen::clearfile(const std::string file_name)
{
    cout << "clearing .." << endl;
    remove(file_name.c_str());
    //std::ofstream ofs;
    //ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
    //ofs.close();
    return;
}
void CodeGen::fill_contents(std::string name, const std::string content, bool append)
{

    std::ofstream outfile;
    if (append)
    {
        outfile.open(name, std::ios_base::app | ios::out);
        if (outfile.fail() || !outfile.is_open())
        {
            cerr << "something wrong -> unable to emit output (permission-denied)" << endl;
            return;
        }
    }
    else
        outfile.open(name, std::ios_base::out);
    outfile << content;
    return;
}

void CodeGen::write(int destination, std::string data)
{
    //0 for writing in header file
    //1 for writing in body
    //2 for writing in main
    if (destination == AT_THE_HEAD)
    {
        //if (!head.empty())
        this->head += data;
        return;
    }
    else if (destination == AT_THE_BODY)
    {
        //if (!body.empty())
        this->body += data;
        return;
    }
    else if (destination == AT_THE_MAIN)
    {
        //if (!main.empty())
        cout << "cont in main:" << main << endl;
        this->main += data;
        return;
    }
    return;
}