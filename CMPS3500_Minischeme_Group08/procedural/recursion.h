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
