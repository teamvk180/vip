#include "ast.h"
#include <vector>
std::string isEnd = "\n";
Expression* Expression::evaluvate()
{
       switch (node)
       {
       case node_type::FUN_CAL:
       {
           if(data=="system.out.println")
           {
               cout << "println called";
           }
           else if(data=="add")
           {
               cout <<"add called"<<endl;
           }
           else if(data=="sub")
           {
               cout <<"sub called"<<endl;
           }
           else if(data=="mul")
           {
               cout <<"mul called"<<endl;
           }
           else if(data=="div")
           {
               cout <<"div called"<<endl;
           }                                 
           break;
       }
       case node_type::BLOCK_NODE:
       {
           cout <<"block called"<<endl;
           if(!expr.empty())
           {
               for(auto const l : expr)
               {
                 cout<< l->evaluvate();
               }
           }
       }
       case node_type::ASSIGN_NODE:
       {
        cout <<"assign called on "<<this->token.lexeme<<endl;
        expr1->evaluvate();
        break;
       }
       case node_type::MOD_CALL:
       {
           cout<<"library called"<<endl;
          // expr1->evaluvate();
           break;
       }
       case node_type::INT_NODE:
       {
           cout<<"int called "<<this->token.lexeme<<endl;
           break;
       }
       case node_type::STR_NODE:
       {
           cout<<"string called "<<this->token.lexeme<<endl;
           break;
       }  
       case node_type::FLOAT_NODE:
       {
           cout<<"float called "<<this->token.lexeme<<endl;
           break;
       }                   
       default:
           break;
       }

        return this;
}