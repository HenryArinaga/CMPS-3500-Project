/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: if.cpp                                  /
  / DATE: 04/11/2026                                    /
*/
#include "if.h"
#include <iostream>

// Handles the built-in if expression
void handleIf(const std::vector<std::string>& expr, Scope* scope)
{
    if (expr.size() != 4)
    {
        std::cout << "Error: invalid if expression\n";
        return;
    }

    std::string condition = expr[1];
    std::string true_branch = expr[2];
    std::string false_branch = expr[3];

    std::string cond_value;
    // If the condition is a literal #t or #f, use it directly
    if (condition == "#t" || condition == "#f")
    {
        cond_value = condition;
    }
    else
    {
        cond_value = lookupScopeEntry(scope, condition);
    }

    if (cond_value == "#t")
    {
        std::cout << true_branch << "\n";
    }
    else
    {
        std::cout << false_branch << "\n";
    }
}
