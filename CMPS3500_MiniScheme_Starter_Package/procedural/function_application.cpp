/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: function_application.cpp                       /
  / DATE: 04/11/2026                                     /
*/
#include "function_application.h"
#include "evaluate.h"
#include "scope.h"
#include "lambda.h"
#include <cctype>

static bool isErrorValue(const std::string &value)
{
    return value == "PARSE_ERROR" ||
           value == "UNDECLARED_IDENTIFIER" ||
           value == "WRONG_ARITY" ||
           value == "TYPE_MISMATCH" ||
           value == "DIVISION_BY_ZERO";
}

// Helper function to check if a token is an integer literal
static bool isIntegerLiteral(const std::string &token)
{
    if (token.empty())
    {
        return false;
    }

    int start = 0;

    if (token[0] == '-')
    {
        if (token.size() == 1)
        {
            return false;
        }

        start = 1;
    }

    for (int i = start; i < (int)token.size(); i++)
    {
        if (!isdigit(token[i]))
        {
            return false;
        }
    }

    return true;
}

// Helper function to extract a part of the expression
static std::vector<std::string> extractPart(
    const std::vector<std::string> &expr,
    int &i)
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

    // Extract the part starting from the current index, handling nested parentheses
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
static bool resolveValue(
    const std::string &token,
    Scope *scope,
    int &result,
    std::string &error)
{
    std::string value = token;

    // If the token is not an integer literal, it must be a variable reference
    if (!isIntegerLiteral(value))
    {
        if (value == "#t" || value == "#f")
        {
            error = "TYPE_MISMATCH";
            return false;
        }

        value = lookupScopeEntry(scope, value);

        if (value == "NOT FOUND")
        {
            error = "UNDECLARED_IDENTIFIER";
            return false;
        }

        if (!isIntegerLiteral(value))
        {
            error = "TYPE_MISMATCH";
            return false;
        }
    }

    result = std::stoi(value);
    return true;
}
// Resolves an expression to an integer value, handling nested expressions as well
static bool resolveExpressionValue(
    const std::vector<std::string> &expr,
    int &i,
    Scope *scope,
    int &result,
    std::string &error)
{
    if (expr[i] != "(")
    {
        if (!resolveValue(expr[i], scope, result, error))
        {
            return false;
        }

        i++;
        return true;
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

    std::string value = evaluate(nested_expr, scope);

    if (isErrorValue(value))
    {
        error = value;
        return false;
    }

    if (!isIntegerLiteral(value))
    {
        error = "TYPE_MISMATCH";
        return false;
    }

    result = std::stoi(value);
    return true;
}
/* Handles function application for built-in functions like +, -, *, /
    as well as user defined lambda functions. It evaluates the operator and arguments,
    checks for errors, and applies the operator or lambda to the arguments. */
std::string handleFunctionApplication(
    const std::vector<std::string> &expr,
    Scope *scope)
{
    // the first token in the expression is the operator or function being applied
    std::string op = expr[0];
    if (op == "(")
    {
        int i = 0;
        std::vector<std::string> lambda_expr = extractPart(expr, i);
        std::vector<std::vector<std::string>> arguments;

        // extract the arguments for the lambda application
        while (i < (int)expr.size())
        {
            arguments.push_back(extractPart(expr, i));
        }

        std::string lambda_value = evaluate(lambda_expr, scope);
        if (isErrorValue(lambda_value))
        {
            return lambda_value;
        }
        return applyLambdaValue(lambda_value, arguments, scope);
    }

    std::string lambda_value = lookupScopeEntry(scope, op);

    // if the operator is not found in the scope, return an error
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
            int value = 0;
            std::string error;

            if (!resolveExpressionValue(expr, i, scope, value, error))
            {
                return error;
            }

            result += value;
        }

        return std::to_string(result);
    }
    // Implement other operations similarly
    else if (op == "-")
    {
        if (expr.size() < 2)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int result = 0;
        std::string error;

        // resolve the first value to initialize the result for subtraction
        if (!resolveExpressionValue(expr, i, scope, result, error))
        {
            return error;
        }

        for (; i < (int)expr.size();)
        {
            int value = 0;

            if (!resolveExpressionValue(expr, i, scope, value, error))
            {
                return error;
            }

            result -= value;
        }

        return std::to_string(result);
    }

    else if (op == "*")
    {
        int result = 1;

        for (int i = 1; i < (int)expr.size();)
        {
            int value = 0;
            std::string error;

            if (!resolveExpressionValue(expr, i, scope, value, error))
            {
                return error;
            }

            result *= value;
        }

        return std::to_string(result);
    }

    else if (op == "/")
    {
        if (expr.size() < 2)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int result = 0;
        std::string error;

        if (!resolveExpressionValue(expr, i, scope, result, error))
        {
            return error;
        }

        for (; i < (int)expr.size();)
        {
            int divisor = 0;

            if (!resolveExpressionValue(expr, i, scope, divisor, error))
            {
                return error;
            }

            if (divisor == 0)
            {
                return "DIVISION_BY_ZERO";
            }

            result /= divisor;
        }

        return std::to_string(result);
    }
    else if (op == "=")
    {
        if (expr.size() < 3)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int left = 0;
        std::string error;

        if (!resolveExpressionValue(expr, i, scope, left, error))
        {
            return error;
        }

        while (i < (int)expr.size())
        {
            int right = 0;

            if (!resolveExpressionValue(expr, i, scope, right, error))
            {
                return error;
            }

            if (left != right)
            {
                return "#f";
            }

            left = right;
        }

        return "#t";
    }
    else if (op == "<")
    {
        if (expr.size() < 3)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int left = 0;
        std::string error;

        if (!resolveExpressionValue(expr, i, scope, left, error))
        {
            return error;
        }

        while (i < (int)expr.size())
        {
            int right = 0;

            if (!resolveExpressionValue(expr, i, scope, right, error))
            {
                return error;
            }

            if (!(left < right))
            {
                return "#f";
            }

            left = right;
        }

        return "#t";
    }
    else if (op == ">")
    {
        if (expr.size() < 3)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int left = 0;
        std::string error;

        if (!resolveExpressionValue(expr, i, scope, left, error))
        {
            return error;
        }

        while (i < (int)expr.size())
        {
            int right = 0;

            if (!resolveExpressionValue(expr, i, scope, right, error))
            {
                return error;
            }

            if (!(left > right))
            {
                return "#f";
            }

            left = right;
        }

        return "#t";
    }
    else if (op == "<=")
    {
        if (expr.size() < 3)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int left = 0;
        std::string error;

        if (!resolveExpressionValue(expr, i, scope, left, error))
        {
            return error;
        }

        while (i < (int)expr.size())
        {
            int right = 0;

            if (!resolveExpressionValue(expr, i, scope, right, error))
            {
                return error;
            }

            if (!(left <= right))
            {
                return "#f";
            }

            left = right;
        }

        return "#t";
    }
    else if (op == ">=")
    {
        if (expr.size() < 3)
        {
            return "WRONG_ARITY";
        }

        int i = 1;
        int left = 0;
        std::string error;

        if (!resolveExpressionValue(expr, i, scope, left, error))
        {
            return error;
        }

        while (i < (int)expr.size())
        {
            int right = 0;

            if (!resolveExpressionValue(expr, i, scope, right, error))
            {
                return error;
            }

            if (!(left >= right))
            {
                return "#f";
            }

            left = right;
        }

        return "#t";
    }
    // unknown function if we get here
    return "UNDECLARED_IDENTIFIER";
}
