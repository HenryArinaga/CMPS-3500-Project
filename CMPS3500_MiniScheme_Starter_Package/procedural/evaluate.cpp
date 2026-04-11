#include "evaluate.h"
#include "parser.h"
#include "if.h"
#include "scope.h"
#include <iostream>
#include "function_application.h"

void evaluate(const std::vector<std::string> &expr, Scope *scope)
{
    if (expr.empty())
    {
        return;
    }

    std::vector<std::string> parsed = parseTokens(expr);

    if (parsed.empty())
    {
        return;
    }

    std::string op = parsed[0];

    if (op == "if")
    {
        handleIf(parsed, scope);
    }
    else if (op == "define")
    {
        // handle_define(parsed, scope);
    }
    else
    {
        if (parsed.size() == 1)
        {
            // variable lookup
            std::string value = lookupScopeEntry(scope, op);
            std::cout << op << " = " << value << "\n";
        }
        else
        {
            // function call
            handleFunctionApplication(parsed, scope);
        }
    }
}
