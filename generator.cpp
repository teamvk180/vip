#include "generator.h"
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <istream>
#include "Token.h"
// Usage example: filePutContents("./yourfile.txt", "content", true);
void gen::filePutContents(const std::string &name, const std::string &content, bool append)
{
    std::ofstream outfile;
    if (append)
        outfile.open(name, std::ios_base::app | ios::out);
    else
        outfile.open(name, std::ios_base::out);
    outfile << content;
}

void gen::explod(std::string head, std::string body, std::string main)
{
    cout << "exploding .." << endl;
    this->filePutContents("tcc/in.c", "", false);
    if (head.length() > 0)
        this->filePutContents("temp/in.c", head, true);
    else
    {
        cout << "head is empty" << endl;
    }
    if (body.length() > 0)
        this->filePutContents("temp/in.c", "\n" + body + "\n", true);
    else
    {
        cout << "body is empty" << endl;
    }
    cout << "main is : " << main << endl;
    if (main.length() > 0)
        this->filePutContents("temp/in.c", "int main() \n{\n" + main + "\n}\n", true);
    else
    {
        cout << "main is empty" << endl;
    }
    return;
}
