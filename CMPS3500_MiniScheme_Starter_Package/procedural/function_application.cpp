/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: function_application.cpp                      /
  / DATE: 04/11/2026                                    /
*/
#include "function_application.h"
#include "evaluate.h"
#include "scope.h"
#include <iostream>
#include <cctype>

// Resolves a token to an integer value
// looking up variables in the scope if necessary
static int resolveValue(const std::string& token, Scope* scope)
{
    std::string val = token;

    if (!isdigit(val[0]) && val[0] != '-')
    {
        val = lookupScopeEntry(scope, val);
    }

    return std::stoi(val);
}

static int resolveExpressionValue(
    const std::vector<std::string>& expr,
    int& i,
    Scope* scope
)
{
    if (expr[i] != "(")
    {
        int value = resolveValue(expr[i], scope);
        i++;
        return value;
    }

    std::vector<std::string> nested_expr;
    int depth = 0;
    // Extract the nested expression
    while (i < (int)expr.size())
    {
        nested_expr.push_back(expr[i]);

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

    return std::stoi(evaluate(nested_expr, scope));
}
// Handles function application for built-in functions like +, -, *, /
std::string handleFunctionApplication(
    const std::vector<std::string>& expr,
    Scope* scope
)
{
    std::string op = expr[0];
    // Handle built-in functions
    if (op == "+")
    {
        int result = 0;

        for (int i = 1; i < (int)expr.size();)
        {
            result += resolveExpressionValue(expr, i, scope);
        }

        std::cout << result << "\n";
        return std::to_string(result);
    }
    // Implement other operations similarly
    else if (op == "-")
    {
        if (expr.size() < 2)
        {
            return "ERROR";
        }

        int i = 1;
        int result = resolveExpressionValue(expr, i, scope);

        for (; i < (int)expr.size();)
        {
            result -= resolveExpressionValue(expr, i, scope);
        }

        std::cout << result << "\n";
        return std::to_string(result);
    }
    
    else if (op == "*")
    {
        int result = 1;

        for (int i = 1; i < (int)expr.size();)
        {
            result *= resolveExpressionValue(expr, i, scope);
        }

        std::cout << result << "\n";
        return std::to_string(result);
    }

    else if (op == "/")
    {
        if (expr.size() < 2)
        {
            return "ERROR";
        }

        int i = 1;
        int result = resolveExpressionValue(expr, i, scope);

        for (; i < (int)expr.size();)
        {
            int divisor = resolveExpressionValue(expr, i, scope);

            if (divisor == 0)
            {
                std::cout << "ERROR: division by zero\n";
                return "ERROR";
            }

            result /= divisor;
        }

        std::cout << result << "\n";
        return std::to_string(result);
    }

    // comparison
    else if (op == "=")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        bool comparison =
            resolveExpressionValue(expr, i, scope) ==
            resolveExpressionValue(expr, i, scope);
        std::string result = comparison ? "#t" : "#f";

        std::cout << result << "\n";
        return result;
    }

    else if (op == "<")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        bool comparison =
            resolveExpressionValue(expr, i, scope) <
            resolveExpressionValue(expr, i, scope);
        std::string result = comparison ? "#t" : "#f";

        std::cout << result << "\n";
        return result;
    }

    else if (op == ">")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        bool comparison =
            resolveExpressionValue(expr, i, scope) >
            resolveExpressionValue(expr, i, scope);
        std::string result = comparison ? "#t" : "#f";

        std::cout << result << "\n";
        return result;
    }

    //unknown function if we get here
    std::cout << "Unknown function: " << op << "\n";
    return "UNKNOWN_FUNCTION";
}
