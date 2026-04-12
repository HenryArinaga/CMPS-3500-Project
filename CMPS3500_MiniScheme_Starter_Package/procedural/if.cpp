/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: if.cpp                                  /
  / DATE: 04/11/2026                                    /
*/
#include "if.h"
#include "evaluate.h"
#include "parser.h"
#include <iostream>

// Handles the built-in if expression
std::string handleIf(const std::vector<std::string>& expr, Scope* scope)
{
    std::vector<std::string> tail(expr.begin() + 1, expr.end());
    std::vector<std::vector<std::string>> parts = splitExpressions(tail);

    if (parts.size() != 3)
    {
        std::cout << "Error: invalid if expression\n";
        return "";
    }

    std::string cond_value = evaluate(parts[0], scope);

    if (cond_value == "#t")
    {
        return evaluate(parts[1], scope);
    }

    if (cond_value == "#f")
    {
        return evaluate(parts[2], scope);
    }

    std::cout << "Error: invalid if condition\n";
    return "";
}
