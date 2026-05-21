/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 3                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: cond.h                                         /
  / DATE: 05/1/2026                                      / 
*/

#ifndef COND_H
#define COND_H

#include <string>
#include <vector>
#include "scope.h"

std::string handleCond(const std::vector<std::string>& expr, Scope* scope);

#endif
