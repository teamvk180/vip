#ifndef GENERATOR_H
#define GENERATOR_H
#include <string>
#include <ios>
#include <fstream>
#include <ostream>
using namespace std;

class gen
{
public:
    void emit(std::string data_r)
    {
        this->filePutContents("temp/in.c", data_r, true);
        return;
    }
    // Usage example: filePutContents("./yourfile.txt", "content", true);
    void filePutContents(const std::string &name, const std::string &content, bool append = false);
    void explod(std::string head, std::string body, std::string main);
    std::string removeDup(string str);

private:
};
#endif