/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: if.h                                  /
  / DATE: 04/11/2026                                    /
*/
#ifndef IF_H
#define IF_H

#include <vector>
#include <string>
#include "scope.h"

std::string handleIf(const std::vector<std::string>& expr, Scope* scope);

#endif
