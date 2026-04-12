/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: lambda.h                                      /
  / DATE: 04/11/2026                                    /
*/
#ifndef LAMBDA_H
#define LAMBDA_H

#include <vector>
#include <string>
#include "scope.h"

// Forward declaration of the handleLambda function
std::string handleLambda(
    const std::vector<std::string>& expr,
    Scope* scope
);

#endif
