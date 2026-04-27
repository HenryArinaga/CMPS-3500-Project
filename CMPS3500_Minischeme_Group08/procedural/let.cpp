/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: let.cpp                                  /
  / DATE: 04/11/2026                                    /
*/

#include "let.h"
#include "evaluate.h"
#include "scope.h"

// Handles the built-in let expression
std::string handleLet(const std::vector<std::string>& expr, Scope* scope)
{
    Scope* new_scope = enterScope(scope);

    int i = 1;

    if (expr[i] != "(") return "ERROR";
    i++;

    while (expr[i] == "(")
    {
        i++;

        std::string var = expr[i];
        i++;

        std::vector<std::string> value_expr;

        if (expr[i] == "(")
        {
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
        }
        else
        {
            value_expr.push_back(expr[i]);
            i++;
        }

        if (expr[i] != ")") return "ERROR";
        i++;

        std::string value = evaluate(value_expr, scope);
        addScopeEntry(new_scope, var, value);
    }

    
    if (expr[i] != ")") return "ERROR";
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
