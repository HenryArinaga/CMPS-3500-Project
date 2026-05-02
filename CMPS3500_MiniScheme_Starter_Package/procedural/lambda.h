/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 3                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: lambda.h                                       /
  / DATE: 05/1/2026                                      / 
*/
#ifndef LAMBDA_H
#define LAMBDA_H

#include <string>
#include <vector>
#include "scope.h"

std::string handleLambda(const std::vector<std::string>& expr, Scope* scope);

bool isLambdaValue(const std::string& value);

std::string applyLambdaValue(const std::string& lambda_value, 
    const std::vector<std::vector<std::string>>& arguments,Scope* scope);

#endif
