/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 3                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: recursion.h                                    /
  / DATE: 05/1/2026                                      / 
*/ 

#ifndef RECURSION_H
#define RECURSION_H

#include <string>
#include <vector>
#include "scope.h"

bool isRecursiveDefinition(const std::vector<std::string>& value_expr);
std::string handleRecursiveDefine(const std::string& name,
    const std::vector<std::string>& value_expr,Scope* scope
);

#endif
