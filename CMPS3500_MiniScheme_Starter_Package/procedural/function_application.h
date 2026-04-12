/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: function_application.h                      /
  / DATE: 04/11/2026                                    /
*/
#ifndef FUNCTION_APPLICATION_H
#define FUNCTION_APPLICATION_H

#include <vector>
#include <string>
#include "scope.h"
// Forward declaration
std::string handleFunctionApplication(
    const std::vector<std::string>& expr,
    Scope* scope
);


#endif
