/*
#include <iostream>
#include <string>
const int INT_TYPE = 233;
const int STRING_TYPE = 28;
struct Expr
{
public:
    Expr(std::string m)
    {
        this->in = m;
    }
    std::string get_m() { return this->in; }

private:
    std::string in;
};

// Recursive CPP program to recursively insert
// a node and recursively print the list.
using namespace std;
struct Node
{
    int type;
    Expr *exp;
    Node *next;
};

// Allocates a new node with given type
Node *newNode(int type, Expr *k)
{
    Node *new_node = new Node;
    new_node->type = type;
    new_node->exp = k;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node at the
// end of linked list using recursion.
Node *insertEnd(Node *head, int type, Expr *k)
{
    // If linked list is empty, create a
    // new node (Assuming newNode() allocates
    // a new node with given type)
    if (head == NULL)
        return newNode(type, k);

    // If we have not reached end, keep traversing
    // recursively.
    else
        head->next = insertEnd(head->next, type, k);
    return head;
}

void traverse(Node *head)
{
    if (head == NULL)
        return;

    // If head is not NULL, print current node
    // and recur for remaining list
    cout << head->type << " ";
    cout << head->exp->get_m() << "\n";
    traverse(head->next);
}

// Driver code
int main()
{
    Node *head = NULL;
    Expr *t = new Expr("hello world");
    Expr *k = new Expr("13");
    head = insertEnd(head, INT_TYPE, k);
    head = insertEnd(head, STRING_TYPE, t);
    traverse(head);
    return 0;
}
*/