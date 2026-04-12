/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: evaluate.cpp                                  /
  / DATE: 04/11/2026                                    /
*/
#include "evaluate.h"
#include "parser.h"
#include "if.h"
#include "scope.h"
#include <iostream>
#include "function_application.h"
#include "let.h"
#include "lambda.h"

// Evaluates a single expression
std::string evaluate(const std::vector<std::string> &expr, Scope *scope)
{
    if (expr.empty())
    {
        return "";
    }
    // Parse the expression first
    std::vector<std::string> parsed = parseTokens(expr);

    if (parsed.empty())
    {
        return "";
    }

    std::string op = parsed[0];
    // Check for built-in operations first
    if (op == "if")
    {
        return handleIf(parsed, scope);
    }
    else if (op == "define")
    {
        // handle_define(parsed, scope);
        return "";
    }
    else if (op == "let")
    {
        return handleLet(parsed, scope);
    }
    else if (op == "lambda")
    {
        return handleLambda(parsed, scope);
    }
    else
    {
        if (parsed.size() == 1)
        {
            if (parsed[0] == "#t" || parsed[0] == "#f")
            {
                return parsed[0];
            }

            bool is_number = true;
            int start = 0;

            if (parsed[0][0] == '-')
            {
                start = 1;
            }

            for (int i = start; i < (int)parsed[0].size(); i++)
            {
                if (parsed[0][i] < '0' || parsed[0][i] > '9')
                {
                    is_number = false;
                }
            }

            if (is_number && start < (int)parsed[0].size())
            {
                return parsed[0];
            }

            // variable lookup
            std::string value = lookupScopeEntry(scope, op);
            return value;
        }
        else
        {
            // function call
            return handleFunctionApplication(parsed, scope);
        }
    }

    return "";
}
