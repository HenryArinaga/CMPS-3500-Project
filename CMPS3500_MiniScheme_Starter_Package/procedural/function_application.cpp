#include "function_application.h"
#include "scope.h"
#include <iostream>
#include <cctype>

static int resolveValue(const std::string& token, Scope* scope)
{
    std::string val = token;

    if (!isdigit(val[0]) && val[0] != '-')
    {
        val = lookupScopeEntry(scope, val);
    }

    return std::stoi(val);
}

std::string handleFunctionApplication(const std::vector<std::string>& expr, Scope* scope)
{
    std::string op = expr[0];

    if (op == "+")
    {
        int result = 0;

        for (int i = 1; i < (int)expr.size(); i++)
        {
            result += resolveValue(expr[i], scope);
        }

        std::cout << result << "\n";
        return std::to_string(result);
    }

    else if (op == "-")
    {
        if (expr.size() < 2)
        {
            return "ERROR";
        }

        int result = resolveValue(expr[1], scope);

        for (int i = 2; i < (int)expr.size(); i++)
        {
            result -= resolveValue(expr[i], scope);
        }

        std::cout << result << "\n";
        return std::to_string(result);
    }

    else if (op == "*")
    {
        int result = 1;

        for (int i = 1; i < (int)expr.size(); i++)
        {
            result *= resolveValue(expr[i], scope);
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

        int result = resolveValue(expr[1], scope);

        for (int i = 2; i < (int)expr.size(); i++)
        {
            int divisor = resolveValue(expr[i], scope);

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

    std::cout << "Unknown function: " << op << "\n";
    return "UNKNOWN_FUNCTION";
}
