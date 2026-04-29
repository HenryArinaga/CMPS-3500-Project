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
#include "lambda.h"
#include <iostream>
#include <cctype>

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
    if (op == "(")
    {
        int i = 0;
        std::vector<std::string> lambda_expr = extractPart(expr, i);
        std::vector<std::vector<std::string>> arguments;

        while (i < (int)expr.size())
        {
            arguments.push_back(extractPart(expr, i));
        }

        std::string lambda_value = evaluate(lambda_expr, scope);
        return applyLambdaValue(lambda_value, arguments, scope);
    }

    std::string lambda_value = lookupScopeEntry(scope, op);

    if (isLambdaValue(lambda_value))
    {
        int i = 1;
        std::vector<std::vector<std::string>> arguments;

        while (i < (int)expr.size())
        {
            arguments.push_back(extractPart(expr, i));
        }

        return applyLambdaValue(lambda_value, arguments, scope);
    }

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
    else if (op == "=")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        int left = resolveExpressionValue(expr, i, scope);

        while (i < (int)expr.size())
        {
            int right = resolveExpressionValue(expr, i, scope);

            if (left != right)
            {
                std::cout << "#f\n";
                return "#f";
            }

            left = right;
        }

        std::cout << "#t\n";
        return "#t";
    }
    else if (op == "<")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        int left = resolveExpressionValue(expr, i, scope);

        while (i < (int)expr.size())
        {
            int right = resolveExpressionValue(expr, i, scope);

            if (!(left < right))
            {
                std::cout << "#f\n";
                return "#f";
            }

            left = right;
        }

        std::cout << "#t\n";
        return "#t";
    }
    else if (op == ">")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        int left = resolveExpressionValue(expr, i, scope);

        while (i < (int)expr.size())
        {
            int right = resolveExpressionValue(expr, i, scope);

            if (!(left > right))
            {
                std::cout << "#f\n";
                return "#f";
            }

            left = right;
        }

        std::cout << "#t\n";
        return "#t";
    }
    else if (op == "<=")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        int left = resolveExpressionValue(expr, i, scope);

        while (i < (int)expr.size())
        {
            int right = resolveExpressionValue(expr, i, scope);

            if (!(left <= right))
            {
                std::cout << "#f\n";
                return "#f";
            }

            left = right;
        }

        std::cout << "#t\n";
        return "#t";
    }
    else if (op == ">=")
    {
        if (expr.size() < 3)
        {
            return "ERROR";
        }

        int i = 1;
        int left = resolveExpressionValue(expr, i, scope);

        while (i < (int)expr.size())
        {
            int right = resolveExpressionValue(expr, i, scope);

            if (!(left >= right))
            {
                std::cout << "#f\n";
                return "#f";
            }

            left = right;
        }

        std::cout << "#t\n";
        return "#t";
    }
    //unknown function if we get here
    std::cout << "Unknown function: " << op << "\n";
    return "UNKNOWN_FUNCTION";
}
