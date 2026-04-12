/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: function_application.cpp                      /
  / DATE: 04/11/2026                                    /
*/
#include "function_application.h"
#include "evaluate.h"
#include "parser.h"
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
    // Check if this is a lambda application
    std::vector<std::vector<std::string>> parts = splitExpressions(expr);

    if (!parts.empty())
    {
        std::string callee_value = evaluate(parts[0], scope);

        if (callee_value.find("LAMBDA:") == 0)
        {
            Scope* new_scope = enterScope(scope);
            std::string encoded = callee_value.substr(7);
            size_t split = encoded.find(':');

            if (split == std::string::npos)
            {
                exitScope(new_scope);
                return "ERROR";
            }

            std::string params_text = encoded.substr(0, split);
            std::string body_text = encoded.substr(split + 1);
            std::vector<std::string> params;
            std::string current_param;

            for (char c : params_text)
            {
                if (c == ',')
                {
                    if (!current_param.empty())
                    {
                        params.push_back(current_param);
                        current_param.clear();
                    }
                }
                else
                {
                    current_param += c;
                }
            }

            if (!current_param.empty())
            {
                params.push_back(current_param);
            }

            std::vector<std::string> body;
            std::string current_body_token;

            for (char c : body_text)
            {
                if (std::isspace(static_cast<unsigned char>(c)))
                {
                    if (!current_body_token.empty())
                    {
                        body.push_back(current_body_token);
                        current_body_token.clear();
                    }
                }
                else
                {
                    current_body_token += c;
                }
            }

            if (!current_body_token.empty())
            {
                body.push_back(current_body_token);
            }

            if ((int)params.size() != (int)parts.size() - 1)
            {
                exitScope(new_scope);
                return "ERROR";
            }

            for (int i = 1; i < (int)parts.size(); i++)
            {
                std::string arg = evaluate(parts[i], scope);
                addScopeEntry(new_scope, params[i - 1], arg);
            }

            std::string result = evaluate(body, new_scope);
            exitScope(new_scope);
            return result;
        }
    }

    std::string op = expr[0];

    // Handle built-in functions
    if (op == "+")
    {
        int result = 0;

        for (int i = 1; i < (int)expr.size();)
        {
            result += resolveExpressionValue(expr, i, scope);
        }

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

        return std::to_string(result);
    }
    
    else if (op == "*")
    {
        int result = 1;

        for (int i = 1; i < (int)expr.size();)
        {
            result *= resolveExpressionValue(expr, i, scope);
        }

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

        return result;
    }

    //unknown function 
    std::cout << "Unknown function: " << op << "\n";
    return "UNKNOWN_FUNCTION";
}
