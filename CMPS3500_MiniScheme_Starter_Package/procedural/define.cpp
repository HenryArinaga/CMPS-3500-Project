/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 3                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: define.cpp                                     /
  / DATE: 05/1/2026                                      /
*/

#include "define.h"
#include "evaluate.h"
#include "recursion.h"
#include <iostream>

// helper function to extract the value expression from a define expression
static std::vector<std::string> extractDefineValue(
    const std::vector<std::string> &expr,
    int &i)
{
    // initialize an empty vector to hold the value expression
    std::vector<std::string> value_expr;

    // check if end of expression reached
    // size is cast to int to avoid signed/unsigned comparison warning
    if (i >= (int)expr.size())
    {
        return value_expr;
    }

    // if the current token is not an opening parenthesis,
    // return it as a single token value expression
    if (expr[i] != "(")
    {
        value_expr.push_back(expr[i]);
        i++;
        return value_expr;
    }

    int depth = 0;

    // while there are more tokens in the expression,
    // keep adding them to value_expr until matching closing parenthesis are found
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

// This function handles the define expression, which has the form
// (define <name> <value_expr>)
std::string handleDefine(const std::vector<std::string> &expr, Scope *scope)
{
    if (expr.size() < 3)
    {
        return "PARSE_ERROR";
    }

    // the second token in the expression is the name of the variable being defined
    std::string name = expr[1];
    int i = 2;
    // extract the value expression starting from the third token
    std::vector<std::string> value_expr = extractDefineValue(expr, i);

    // check for parse errors, name cannot be certain tokens or empty
    if (name == "(" || name == ")" || value_expr.empty() || i != (int)expr.size())
    {
        return "PARSE_ERROR";
    }

    // if the value expression is a recursive definition,
    // handle it with the recursive function
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

    // if no errors, add the name and value to the current scope
    // and return an empty string
    addScopeEntry(scope, name, value);
    return "";
}
