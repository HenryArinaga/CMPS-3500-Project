/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: let.cpp                                        /
  / DATE: 04/11/2026                                     /
*/

#include "let.h"
#include "evaluate.h"
#include "scope.h"

static std::vector<std::string> extractLetValue(
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

// Handles the built-in let expression
std::string handleLet(const std::vector<std::string>& expr, Scope* scope)
{
    Scope* new_scope = enterScope(scope);

    int i = 1;

    if (i >= (int)expr.size() || expr[i] != "(") return "PARSE_ERROR";
    i++;

    while (i < (int)expr.size() && expr[i] == "(")
    {
        i++;

        if (i >= (int)expr.size())
        {
            exitScope(new_scope);
            return "PARSE_ERROR";
        }

        std::string var = expr[i];
        i++;

        std::vector<std::string> value_expr = extractLetValue(expr, i);

        if (value_expr.empty() || i >= (int)expr.size())
        {
            exitScope(new_scope);
            return "PARSE_ERROR";
        }

        i++;

        std::string value = evaluate(value_expr, scope);
        if (value == "PARSE_ERROR" ||
            value == "UNDECLARED_IDENTIFIER" ||
            value == "WRONG_ARITY" ||
            value == "TYPE_MISMATCH" ||
            value == "DIVISION_BY_ZERO")
        {
            exitScope(new_scope);
            return value;
        }
        addScopeEntry(new_scope, var, value);
    }

    
    if (i >= (int)expr.size() || expr[i] != ")")
    {
        exitScope(new_scope);
        return "PARSE_ERROR";
    }
    i++;

    std::vector<std::string> body;

    // Extract the body of the let expression
    while (i < (int)expr.size())
    {
        body.push_back(expr[i]);
        i++;
    }

    std::string result = evaluate(body, new_scope);

    exitScope(new_scope);

    return result;
}
