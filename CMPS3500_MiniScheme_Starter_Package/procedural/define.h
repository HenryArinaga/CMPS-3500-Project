#ifndef DEFINE_H
#define DEFINE_H

#include <vector>
#include <string>
#include "scope.h"

std::string handleDefine(
    const std::vector<std::string>& expr,Scope* scope);

#endif
