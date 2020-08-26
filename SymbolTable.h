#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;
/*
___________________________________
Name |  	Type 	 |     Scope
------------------------------
add  | 	function |	  global
a 	 |   int     |  	function parameter
b 	 |   int 	   |   function parameter
sum  |	 int 	   |   local
____________________________________


struct Node
{
private:
    // Token mtoken;
    string midentifier, mscope;
    int mIndex;

public:
    Node(string identifier, string scope, int index)
        : midentifier(identifier), mscope(scope), mIndex(index)
    {
    }
    void print()
    {
        cout << "key Name:" << midentifier
             << "\nScope: " << mscope
             << "\nhash : " << mIndex << endl;
    }
    friend class symbol_tab;
};

class symbol_tab
{
private:
    std::vector<Node> kmap;

public:
    bool insert(string kidentifier, string kscope, int index);
    int find(std::string id);
    bool modify(std::string id, string kscope, int index);
    bool delete_this(std::string id);
    std::string kind(std::string symbol);
};
*/
#endif
