#include "cond.h"
#include "evaluate.h"

static std::vector<std::string> extractPart(
    const std::vector<std::string>& expr,
    int& i
)
{
    std::vector<std::string> part;

    if (i >= (int)expr.size())
    {
        return part;
    }

    if (expr[i] != "(")
    {
        part.push_back(expr[i]);
        i++;
        return part;
    }

    int depth = 0;

    while (i < (int)expr.size())
    {
        part.push_back(expr[i]);

        if (expr[i] == "(")
        {
            depth++;
        }
        else if (expr[i] == ")")
        {
            depth--;

            if (depth == 0)
            {
                i++;
                break;
            }
        }

        i++;
    }

    return part;
}

std::string handleCond(const std::vector<std::string>& expr, Scope* scope)
{
    if (expr.size() < 2)
    {
        return "PARSE_ERROR";
    }

    int i = 1;
    bool saw_else = false;

    while (i < (int)expr.size())
    {
        std::vector<std::string> clause = extractPart(expr, i);

        if (clause.size() < 3 || clause[0] != "(" || clause[clause.size() - 1] != ")")
        {
            return "PARSE_ERROR";
        }

        std::vector<std::string> parsed_clause;

        for (int j = 1; j < (int)clause.size() - 1; j++)
        {
            parsed_clause.push_back(clause[j]);
        }

        int clause_index = 0;
        std::vector<std::string> test_expr = extractPart(parsed_clause, clause_index);
        std::vector<std::string> result_expr = extractPart(parsed_clause, clause_index);

        if (test_expr.empty() || result_expr.empty() || clause_index != (int)parsed_clause.size())
        {
            return "PARSE_ERROR";
        }

        if (test_expr.size() == 1 && test_expr[0] == "else")
        {
            if (saw_else || i != (int)expr.size())
            {
                return "PARSE_ERROR";
            }

            saw_else = true;
            return evaluate(result_expr, scope);
        }

        std::string test_value = evaluate(test_expr, scope);

        if (test_value == "PARSE_ERROR" ||
            test_value == "UNDECLARED_IDENTIFIER" ||
            test_value == "WRONG_ARITY" ||
            test_value == "TYPE_MISMATCH" ||
            test_value == "DIVISION_BY_ZERO")
        {
            return test_value;
        }

        if (test_value == "#t")
        {
            return evaluate(result_expr, scope);
        }

        if (test_value != "#f")
        {
            return "TYPE_MISMATCH";
        }
    }

    return "PARSE_ERROR";
}
