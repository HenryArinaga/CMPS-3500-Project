#include "recursion.h"
#include "evaluate.h"
#include "scope.h"

bool isRecursiveDefinition(const std::vector<std::string>& value_expr)
{
    return !value_expr.empty() && value_expr[0] == "(" &&
           value_expr.size() > 1 && value_expr[1] == "lambda";
}

std::string handleRecursiveDefine(
    const std::string& name,
    const std::vector<std::string>& value_expr,
    Scope* scope
)
{
    std::string value = evaluate(value_expr, scope);
    addScopeEntry(scope, name, value);
    return "";
}
