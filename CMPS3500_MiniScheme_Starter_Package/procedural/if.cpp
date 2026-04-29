/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: if.cpp                                  /
  / DATE: 04/11/2026                                    /
*/
#include "if.h"
#include "evaluate.h"
#include <iostream>

static std::vector<std::string> extractIfPart(
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

static std::string evaluateIfPart(
    const std::vector<std::string>& part,
    Scope* scope
)
{
    if (part.empty())
    {
        return "";
    }

    if (part.size() == 1 && (part[0] == "#t" || part[0] == "#f"))
    {
        return part[0];
    }

    return evaluate(part, scope);
}

// Handles the built-in if expression
std::string handleIf(const std::vector<std::string>& expr, Scope* scope)
{
    int i = 1;
    std::vector<std::string> condition = extractIfPart(expr, i);
    std::vector<std::string> true_branch = extractIfPart(expr, i);
    std::vector<std::string> false_branch = extractIfPart(expr, i);

    if (
        condition.empty() ||
        true_branch.empty() ||
        false_branch.empty() ||
        i != (int)expr.size()
    )
    {
        std::cout << "Error: invalid if expression\n";
        return "";
    }

    std::string cond_value = evaluateIfPart(condition, scope);

    if (cond_value == "#t")
    {
        std::string result = evaluateIfPart(true_branch, scope);
        std::cout << result << "\n";
        return result;
    }
    else
    {
        std::string result = evaluateIfPart(false_branch, scope);
        std::cout << result << "\n";
        return result;
    }
}
