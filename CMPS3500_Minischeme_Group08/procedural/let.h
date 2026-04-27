/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: let.h                                  /
  / DATE: 04/11/2026                                    /
*/
#ifndef LET_H
#define LET_H

#include <vector>
#include <string>
#include "scope.h"

std::string handleLet(
    const std::vector<std::string>& expr,
    Scope* scope
);

#endif
