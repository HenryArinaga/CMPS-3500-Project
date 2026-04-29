#include "lambda.h"
#include "evaluate.h"
#include <string>

static std::string joinTokens(
    const std::vector<std::string>& tokens,
    int start,
    int end
)
{
    std::string result;

    for (int i = start; i < end; i++)
    {
        if (!result.empty())
        {
            result += " ";
        }

        result += tokens[i];
    }

    return result;
}

static std::vector<std::string> splitString(
    const std::string& text,
    char delimiter
)
{
    std::vector<std::string> parts;
    std::string current;

    for (int i = 0; i < (int)text.size(); i++)
    {
        if (text[i] == delimiter)
        {
            parts.push_back(current);
            current.clear();
        }
        else
        {
            current += text[i];
        }
    }

    parts.push_back(current);
    return parts;
}

static std::vector<std::string> splitBySpace(const std::string& text)
{
    std::vector<std::string> tokens;
    std::string current;

    for (int i = 0; i < (int)text.size(); i++)
    {
        if (text[i] == ' ')
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current.clear();
            }
        }
        else
        {
            current += text[i];
        }
    }

    if (!current.empty())
    {
        tokens.push_back(current);
    }

    return tokens;
}

std::string handleLambda(const std::vector<std::string>& expr, Scope* scope)
{
    (void)scope;

    if (expr.size() < 5)
    {
        return "ERROR";
    }

    if (expr[1] != "(")
    {
        return "ERROR";
    }

    int i = 2;
    std::vector<std::string> params;

    while (i < (int)expr.size() && expr[i] != ")")
    {
        if (expr[i] == "(")
        {
            return "ERROR";
        }

        params.push_back(expr[i]);
        i++;
    }

    if (i >= (int)expr.size() || expr[i] != ")")
    {
        return "ERROR";
    }

    i++;

    if (i >= (int)expr.size())
    {
        return "ERROR";
    }

    std::string param_text;

    for (int j = 0; j < (int)params.size(); j++)
    {
        if (!param_text.empty())
        {
            param_text += ",";
        }

        param_text += params[j];
    }

    std::string body_text = joinTokens(expr, i, expr.size());

    if (body_text.empty())
    {
        return "ERROR";
    }

    return "LAMBDA|" + param_text + "|" + body_text;
}

bool isLambdaValue(const std::string& value)
{
    return value.size() >= 7 && value.substr(0, 7) == "LAMBDA|";
}

std::string applyLambdaValue(
    const std::string& lambda_value,
    const std::vector<std::vector<std::string>>& arguments,
    Scope* scope
)
{
    if (!isLambdaValue(lambda_value))
    {
        return "ERROR";
    }

    std::vector<std::string> parts = splitString(lambda_value, '|');

    if (parts.size() != 3)
    {
        return "ERROR";
    }

    std::vector<std::string> params;

    if (!parts[1].empty())
    {
        params = splitString(parts[1], ',');
    }

    if ((int)params.size() != (int)arguments.size())
    {
        return "ERROR";
    }

    Scope* lambda_scope = enterScope(scope);

    for (int i = 0; i < (int)params.size(); i++)
    {
        std::string value = evaluate(arguments[i], scope);
        addScopeEntry(lambda_scope, params[i], value);
    }

    std::vector<std::string> body = splitBySpace(parts[2]);
    std::string result = evaluate(body, lambda_scope);
    exitScope(lambda_scope);
    return result;
}
