#include <cstdio>
#include <cassert>

/***********************************************************************************************************************
 
 A expression solver implemented by recursive descent parser
 
***********************************************************************************************************************/

/************************************************************************/
/* The grammar should be 
   E -> T + T - T
   T -> Q * Q / Q
   Q -> -F
   F -> (N)
   N -> Number or Expression
   E is the input expression, T, Q, F, N are terms at different level*/
/************************************************************************/

class ExpSolver
{
public:
    ExpSolver(void) : idx_(0), eq_(NULL), token_tpye_(END){};
    ~ExpSolver(void){};

    float SolveExp(const char *eq)
    {
        assert(eq != NULL);
        double result;
        eq_ = eq;
        idx_ = 0;
        ReadNextToken();

        assert(token_tpye_ != ERROR && token_tpye_ != END);

        result = CalPlusMinus();

        ReadNextToken();
        assert(token_tpye_ == END);

        return (float)result;
    }

private:
    // Store a token.
    struct Token
    {
        int start; // The token's first index in expression string(eq_)
        int len;   // Length
        Token(void) : start(0), len(0){};
        Token(int s, int l) : start(s), len(l){};
    };

    enum TokenType
    {
        NUMBER = 0,
        OPERATOR,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        ERROR,
        END
    };

    int idx_; // Current index
    const char *eq_;
    Token token_;          // Current token
    TokenType token_tpye_; // Current token type

    // E -> T + T - T.
    double CalPlusMinus(void)
    {
        double res;
        res = CalMulDivide();

        while (Peek() == '+' || Peek() == '-')
        {
            char op = Peek();
            ReadNextToken();
            assert(token_tpye_ == OPERATOR);
            ReadNextToken();

            double inter_res = CalMulDivide();

            if (op == '+')
            {
                res += inter_res;
            }
            else
            {
                res -= inter_res;
            }
        }

        return res;
    };

    // T -> Q * Q / Q
    double CalMulDivide(void)
    {
        double res;
        res = CalUnaryMinus();

        while (Peek() == '*' || Peek() == '/')
        {
            char op = Peek();
            ReadNextToken();
            assert(token_tpye_ == OPERATOR);
            ReadNextToken();

            double inter_res = CalUnaryMinus();

            if (op == '*')
            {
                res *= inter_res;
            }
            else
            {
                assert(inter_res != 0);
                res /= inter_res;
            }
        }

        return res;
    };

    // Q -> -F
    double CalUnaryMinus(void)
    {
        double res;
        assert(idx_ > 0);
        bool is_negtive = eq_[token_.start] == '-';

        if (is_negtive)
        {
            ReadNextToken();
            assert(token_tpye_ != ERROR && token_tpye_ != END);
            res = CalParentheses();
            res = -res;
        }
        else
        {
            assert(token_tpye_ != OPERATOR);
            res = CalParentheses();
        }
        return res;
    };

    // F -> (N)
    double CalParentheses(void)
    {
        double res;
        assert(idx_ > 0);
        if (token_tpye_ == LEFT_BRACKET)
        {
            ReadNextToken();
            assert(token_tpye_ != ERROR && token_tpye_ != END);

            res = CalPlusMinus();

            ReadNextToken();
            assert(token_tpye_ == RIGHT_BRACKET);
        }
        else
        {

            if (token_tpye_ == NUMBER) //Atom
                res = TokenToDouble();
            else
                res = CalUnaryMinus();
        }

        return res;
    };

    // Read next token into token_, and set its type into token_type_
    void ReadNextToken(void)
    {
        token_.start = 0;
        token_.len = 0;
        assert(eq_ != NULL);
        if (eq_[idx_] == '\0')
        {
            token_tpye_ = END;
            return;
        }

        while (eq_[idx_] != '\0' && (eq_[idx_] == ' ' || eq_[idx_] == '\t' || eq_[idx_] == '\n'))
        {
            idx_++;
        }

        if (eq_[idx_] == '\0')
        {
            token_tpye_ = END;
            return;
        }

        if (IsOperator(eq_[idx_]))
        {
            token_.start = idx_;
            token_.len = 1;
            idx_++;
            token_tpye_ = OPERATOR;
            return;
        }

        if (eq_[idx_] == '(')
        {
            token_.start = idx_;
            token_.len = 1;
            idx_++;
            token_tpye_ = LEFT_BRACKET;
            return;
        }

        if (eq_[idx_] == ')')
        {
            token_.start = idx_;
            token_.len = 1;
            idx_++;
            token_tpye_ = RIGHT_BRACKET;
            return;
        }

        if (IsDigit(eq_[idx_]))
        {
            token_.start = idx_;
            while ((IsDigit(eq_[idx_]) || eq_[idx_] == '.') && eq_[idx_] != '\0')
            {
                token_.len++;
                idx_++;
            }
            token_tpye_ = NUMBER;
            return;
        }
        token_tpye_ = ERROR;
    }

    bool IsOperator(char c)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool IsDigit(char c)
    {
        if (c >= '0' && c <= '9')
            return true;
        else
            return false;
    }

    // Convert current token into a double. Current token must be a number
    double TokenToDouble()
    {
        assert(token_tpye_ == NUMBER);
        const char *str = &eq_[token_.start];
        int len = token_.len;
        assert(str != NULL);
        double integer = 0;
        double fraction = 0;
        bool is_fraction = false;
        long divisor = 1;
        long sign = 1;

        if (*str == '-')
        {
            str++;
            sign = -1;
            len--;
        }

        for (int idx = 0; idx < len; idx++)
        {
            if (str[idx] >= '0' && str[idx] <= '9')
            {
                if (is_fraction)
                {
                    fraction = fraction * 10 + (str[idx] - '0');
                    divisor *= 10;
                }
                else
                {
                    integer = integer * 10 + (str[idx] - '0');
                }
            }
            else if (str[idx] == '.')
            {
                assert(!is_fraction);
                is_fraction = true;
            }
            else
            {
                assert(false);
            }
        }
        return sign * (integer + fraction / divisor);
    }

    // Peek the next character without moving idx_
    char Peek()
    {
        int peek_idx = idx_;
        while (eq_[peek_idx] != '\0' && (eq_[peek_idx] == ' ' || eq_[peek_idx] == '\t' || eq_[peek_idx] == '\n'))
        {
            peek_idx++;
        }
        return eq_[peek_idx];
    }
};

static float solve(const char *eq)
{
    // IMPLEMENT ME
    assert(eq != NULL);
    ExpSolver exp_solver;
    return exp_solver.SolveExp(eq);
}

const char *const kExpressions[] = {
    "-((6+4))* -(2+2) - -1",
    "6/5-4-45+3.08",
    "0.34+ -34/45-2",
    "(0.03)*73-2",
    "(20-23 + -5 * (12 / (34 + 3) - 3))",
    "-25 + 4 * -(32 - 45 / 5 - -6)",
    "0.0003101 - 34 * (4 + 5) / 23",
    "1 + ((1 + 1) + 3) + 4 * 5 / 6 - 7",
    "9 / 8/7 /6/5/4  /  3 /  2/1",
    "-( -(-( -(2+3*4)+2 )-1)+ 0)",
};

//These are rounded.
const float kAnswers[] = {
    41.0f,
    -44.72f,
    -2.41556f,
    0.19f,
    10.3784f,
    -141.0f,
    -13.3040f,
    2.33333f,
    0.00022321f,
    11.0f,
};

int main(int argc, char *argv[])
{
    for (int i = 0; i < (sizeof(kExpressions) / sizeof(kExpressions[0])); ++i)
        printf("Expression #%d: %s = %g = %g\n", i, kExpressions[i], solve(kExpressions[i]), kAnswers[i]);

    return 0;
}