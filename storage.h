/*
#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <vector>
using namespace std;
class storage
{
public:
    void put_main(std::string m)
    {
        cout << "settt .. ";

        fstream f2;
        f2.open("temp/in.vpx", ios::app | ios::out);
        f2 << m;
        f2.close();
        m.clear();
    }
    std::string get_main()
    {
        std::ifstream inFile;
        inFile.open("temp/in.vpx"); //open the input file

        std::stringstream strStream;
        strStream << inFile.rdbuf();       //read the file
        std::string str = strStream.str(); //str holds the content of the file

        //std::cout << str << "\n"; //you can do anything with the string!!!
        return str;
    }
};
#endif
*/