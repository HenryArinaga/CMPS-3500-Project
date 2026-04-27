/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: evaluate.h                                  /
  / DATE: 04/11/2026                                    /
*/
#ifndef EVALUATE_H
#define EVALUATE_H

#include <vector>
#include <string>
#include "scope.h"
// Forward declaration
std::string evaluate(const std::vector<std::string>& expr, Scope* scope);

#endif
