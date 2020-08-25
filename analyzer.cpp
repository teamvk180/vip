#include "analyzer.h"
#include "Exception.h"
void Analyzer::analyze_variable(Token t)
{
    switch (t.type())
    {
    case ID:
    {
        break;
    }
    case INT_TYPE:
    {
        break;
    }

    case STRING_TYPE:
    {
        break;
    }

    case FLOAT_TYPE:
    {
        break;
    }

    case TYPE_INT:
    {
        break;
    }
    case BOOL_TRUE:
    {
        break;
    }
    case BOOL_FALSE:
    {
        break;
    }

    case TYPE_DRIVER:
    {
        break;
    }

    case TYPE_CONST:
    {
        break;
    }

    break;
    case TYPE_INVALID:
    {
        break;
    }
    default:
    {
        //throw InvalidDataTypeException("unknown datatype " + t.lexeme());
        break;
    }
    }
    return;
}