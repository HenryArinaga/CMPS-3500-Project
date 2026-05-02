/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 3                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: define.h                                       /
  / DATE: 05/1/2026                                      / 
*/

#ifndef DEFINE_H
#define DEFINE_H

#include <vector>
#include <string>
#include "scope.h"

std::string handleDefine(const std::vector<std::string>& expr,Scope* scope);

#endif
