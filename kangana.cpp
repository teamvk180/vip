#include "parser.h"
#include "VIP_signal.h"
#include "token.h"
#include "ast.h"

int Parser::get_type()
{
    cout << "T is " << currentToken.lexeme() << endl;
    int type = T_NOTHING;
    switch (currentToken.type())
    {
    case SEMICOLON:
    {
        return type;
        update();
        break; }
    case ASSIGNMENT:
    {
        return ASSIGNMENT;
        break; }
    case GREATER_THAN:
    {
        return T_BOOLEAN_EXPR;
        break; }
    case GREATER_THAN_EQ:
    {
        return T_BOOLEAN_EXPR;
        break; }
    case NOT_EQUAL:
    {
        return T_BOOLEAN_EXPR;
        break; }
    case LESS_THAN:
    {
        return T_BOOLEAN_EXPR;
        break; }
    case LESS_THAN_EQ:
    {
        return T_BOOLEAN_EXPR;
        break; }
    case ADD:
    {
        return T_ARITHEMATIC_EXPR;
        break; }
    case SUBTRACT:
    {
        return T_ARITHEMATIC_EXPR;
        break; }
    case MULTIPLY:
    {
        return T_ARITHEMATIC_EXPR;
        break; }
    case DIVIDE:
    {
        return T_ARITHEMATIC_EXPR;
        break; }
    case AND:
    {
        return T_CMP;
        break; }
    case OR:
    {
        return T_CMP;
        break; }
    case NOT:
    {
        return T_CMP;
        break; }
    case IN:
    {
        return IN;
        break; }
    case TAR_ID:
    {
        return TAR_ID;
        break; }
    case L_BRACK:
    {
        return T_L_BRACK_BEGIN;
        break; }
    case R_BRAK:
    {
        return T_NOTHING;
        break; }
    case L_PAREN:
    {
        return T_L_PAREN_BEGIN;
        break; }
    case R_PAREN:
    {
        return T_L_PAREN_END;
        break; }
    case L_BRACE:
    {
        return T_L_BRACE_BEGIN;
        break; }
    case R_BRACE:
    {
        return T_L_BRACE_END;
        break; }
    case SERVE:
    {
        return T_NOTHING;
        break; }
    case ID:
    {
        return T_VAR_TYPE;
        break; }
    case INT_TYPE:
    {
        return T_VAR_TYPE;
        break; }
    case STRING_TYPE:
    {
        return T_VAR_TYPE;
        break; }
    case FLOAT_TYPE:
    {
        return T_VAR_TYPE;
        break; }
    case BOOL_FALSE:
    {
        return T_VAR_TYPE;
        break; }
    case BOOL_TRUE:
    {
        return T_VAR_TYPE;
        break; }
    case ERROR:
    {
        return ERROR;
        break; }
    case COMPARE:
    {
        return T_CMP;
        break; }
    case EXTENDS:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case COMMA:
    {
        update();
        return type;
        break; }
    case NAMESPACE:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case RETURN:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case USING:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case AS:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case TYPE_STRING:
    {
        return T_VAR_TYPE;
        break; }
    case TYPE_METHOD:
    {
        return T_VAR_TYPE;
        break; }
    case BUFFER_TYPE:
    {
        return T_VAR_TYPE;
        break; }
    case EOS:
    {
        finished = true;
        //set symtab transfer parser->ast here
        break;
        break; }
    case EOP:
    {
        update();
        return T_NOTHING;
        break; }
    case NEW:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case NEGATIVE_FLOAT_TYPE:
    {
        return T_VAR_TYPE;
        break; }
    case NEGATIVE_INT_TYPE:
    {
        return T_VAR_TYPE;
        break; }
    case TYPE_CONST:
    {
        return T_VAR_TYPE;
        break; }

    case SIZEOF:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case BSIZEOF:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case FSIZEOF:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case TYPEOF:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case BTYPEOF:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case PRIVATE:
    {
        return T_VAR_TYPE;
        break; }
    case CHILD:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case CALL:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case SELF:
    {
        return T_BUILT_IN_METHOD_CALL;
        break; }
    case EOH:
    {
        eoh_parsed = true;
        break; }
    case POWER:
    {
        return type;
        break; }
    case IF:
    {
        return type;
        break; }
    case WHILE:
    {
        return type;
        break; }
    case ELSE:
    {
        return type;
        break; }
    case DOUBLE_ADD:
    {
        return T_ARITHEMATIC_EXPR;
        break; }
    case DOUBLE_SUBRACT:
    {
        return T_ARITHEMATIC_EXPR;
        break; }
    case T_FILE:
    {
        return type;
        break;
    }
    case MOD:
    {
        return T_ARITHEMATIC_EXPR;
        break;
    }
    case TYPE_DRIVER:
    {
        return type;
        break;
    }
    case TYPE_INVALID:
    {
        return type;
        break;
    }
    case THIS:
    {
        return T_BUILT_IN_METHOD_CALL;
        break;
    }
    default:
    {
        throw logic_error("unrecognized operator " + currentToken.lexeme());
        break;

    }
    }
    return T_NOTHING;
}