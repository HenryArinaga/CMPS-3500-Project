#include "define.h"
#include "evaluate.h"
#include "recursion.h"
#include <iostream>

static std::vector<std::string> extractDefineValue(
    const std::vector<std::string>& expr,
    int& i
)
{
    std::vector<std::string> value_expr;

    if (i >= (int)expr.size())
    {
        return value_expr;
    }

    if (expr[i] != "(")
    {
        value_expr.push_back(expr[i]);
        i++;
        return value_expr;
    }

    int depth = 0;

    while (i < (int)expr.size())
    {
        value_expr.push_back(expr[i]);

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

    return value_expr;
}

std::string handleDefine(const std::vector<std::string>& expr, Scope* scope)
{
    if (expr.size() < 3)
    {
        return "PARSE_ERROR";
    }

    std::string name = expr[1];
    int i = 2;
    std::vector<std::string> value_expr = extractDefineValue(expr, i);

    if (name == "(" || name == ")" || value_expr.empty() || i != (int)expr.size())
    {
        return "PARSE_ERROR";
    }

    if (isRecursiveDefinition(value_expr))
    {
        return handleRecursiveDefine(name, value_expr, scope);
    }

    std::string value = evaluate(value_expr, scope);
    if (value == "PARSE_ERROR" ||
        value == "UNDECLARED_IDENTIFIER" ||
        value == "WRONG_ARITY" ||
        value == "TYPE_MISMATCH" ||
        value == "DIVISION_BY_ZERO")
    {
        return value;
    }
    addScopeEntry(scope, name, value);
    return "";
}
