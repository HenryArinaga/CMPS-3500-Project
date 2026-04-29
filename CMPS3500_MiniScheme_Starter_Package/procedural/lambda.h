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
