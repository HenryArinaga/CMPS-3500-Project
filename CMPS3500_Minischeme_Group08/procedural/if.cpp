/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: if.cpp                                         /
  / DATE: 04/11/2026                                     /
*/
#include "if.h"
#include "evaluate.h"
#include <iostream>

// Helper function to extract a part of the expression,
// can be either a single token or a parenthesized sub expression
static std::vector<std::string> extractIfPart(
    const std::vector<std::string> &expr,
    int &i)
{
    std::vector<std::string> part;

    // Check if end of expression reached
     // size is cast to int to avoid signed/unsigned comparison warning
    if (i >= (int)expr.size())
    {
        return part;
    }

    // If the current token is not an opening parenthesis 
    // return it as a single token part
    if (expr[i] != "(")
    {
        part.push_back(expr[i]);
        i++;
        return part;
    }

    int depth = 0;

    // while there are more tokens in the expression,
    // keep adding them to value_expr until matching closing parenthesis are found
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


static std::string evaluateIfPart(
    const std::vector<std::string> &part,
    Scope *scope)
{
    if (part.empty())
    {
        return "";
    }
    // If the part is a single token that is #t or #f, return it directly
    if (part.size() == 1 && (part[0] == "#t" || part[0] == "#f"))
    {
        return part[0];
    }

    return evaluate(part, scope);
}

// Handles the built-in if expression
std::string handleIf(const std::vector<std::string> &expr, Scope *scope)
{
    int i = 1;
    std::vector<std::string> condition = extractIfPart(expr, i);
    std::vector<std::string> true_branch = extractIfPart(expr, i);
    std::vector<std::string> false_branch = extractIfPart(expr, i);

    if (
        condition.empty() ||
        true_branch.empty() ||
        false_branch.empty() ||
        i != (int)expr.size())
    {
        return "PARSE_ERROR";
    }

    std::string cond_value = evaluateIfPart(condition, scope);

    if (cond_value == "PARSE_ERROR" ||
        cond_value == "UNDECLARED_IDENTIFIER" ||
        cond_value == "WRONG_ARITY" ||
        cond_value == "TYPE_MISMATCH" ||
        cond_value == "DIVISION_BY_ZERO")
    {
        return cond_value;
    }

    if (cond_value == "#t")
    {
        return evaluateIfPart(true_branch, scope);
    }

    if (cond_value == "#f")
    {
        return evaluateIfPart(false_branch, scope);
    }

    return "TYPE_MISMATCH";
}
