/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga    /
  / ASGT: CHECKPOINT 3                                     /
  / ORGN: CSUB - CMPS 3500                                 /
  / FILE: lambda.cpp                                       /
  / DATE: 05/1/2026                                        / 
*/
#include "lambda.h"
#include "evaluate.h"
#include <string>

// Helper function to combine tokens into a single string with spaces
static std::string combineTokens(
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

// Helper function to split a string by a delimiter into a vector of strings
// delimiter is a single character that separates the parts of the string
static std::vector<std::string> splitString(
    const std::string& text,
    char delimiter
)
{
    std::vector<std::string> parts;
    std::string current;

    for (int i = 0; i < (int)text.size(); i++)
    {
        // if the current character is the delimiter
        // add the current part to the parts vector and clear it
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

// Helper function to split a string by spaces into a vector of strings
static std::vector<std::string> splitBySpace(const std::string& text)
{
    std::vector<std::string> tokens;
    std::string current;

    // split the text by spaces, adding each token to the tokens vector
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

/* this function handles the built in lambda expression by parsing the parameter
    list and body of the lambda, and returning a string representation of the lambda that 
    encodes the parameter
*/
std::string handleLambda(const std::vector<std::string>& expr, Scope* scope)
{
    (void)scope;

    if (expr.size() < 5)
    {
        return "PARSE_ERROR";
    }

    if (expr[1] != "(")
    {
        return "PARSE_ERROR";
    }

    int i = 2;
    std::vector<std::string> params;

    // extract the parameter list of the lambda expression, 
    // which is a list of tokens until the next closing parenthesis
    while (i < (int)expr.size() && expr[i] != ")")
    {
        if (expr[i] == "(")
        {
            return "PARSE_ERROR";
        }

        params.push_back(expr[i]);
        i++;
    }

    if (i >= (int)expr.size() || expr[i] != ")")
    {
        return "PARSE_ERROR";
    }

    i++;

    if (i >= (int)expr.size())
    {
        return "PARSE_ERROR";
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

    // combine the remaining tokens in the expression into 
    // a single string for the body of the lambda
    std::string body_text = combineTokens(expr, i, expr.size());

    if (body_text.empty())
    {
        return "PARSE_ERROR";
    }

    return "LAMBDA|" + param_text + "|" + body_text;
}

// Helper function to check if a value is a lambda value
// which is lambda(value 1 | value n ...) 
bool isLambdaValue(const std::string& value)
{
    return value.size() >= 7 && value.substr(0, 7) == "LAMBDA|";
}

// This function applies a lambda_value to a list of 
// arguments by evaluating the body of the lambda
std::string applyLambdaValue(
    const std::string& lambda_value,
    const std::vector<std::vector<std::string>>& arguments,
    Scope* scope
)
{
    if (!isLambdaValue(lambda_value))
    {
        return "TYPE_MISMATCH";
    }
    
    /* split the lambda value into its parameter list and body using 
     the delimiter which is "|"
     the delimiter is used to separate the parameter list and body 
    of the lambda in the string representation of the lambda value */
    std::vector<std::string> parts = splitString(lambda_value, '|');

    if (parts.size() != 3)
    {
        return "TYPE_MISMATCH";
    }

    std::vector<std::string> params;

    if (!parts[1].empty())
    {
        params = splitString(parts[1], ',');
    }

    if ((int)params.size() != (int)arguments.size())
    {
        return "WRONG_ARITY";
    }

    Scope* lambda_scope = enterScope(scope);

    for (int i = 0; i < (int)params.size(); i++)
    {
        std::string value = evaluate(arguments[i], scope);
        if (value == "PARSE_ERROR" ||
            value == "UNDECLARED_IDENTIFIER" ||
            value == "WRONG_ARITY" ||
            value == "TYPE_MISMATCH" ||
            value == "DIVISION_BY_ZERO")
        {
            exitScope(lambda_scope);
            return value;
        }
        addScopeEntry(lambda_scope, params[i], value);
    }

    std::vector<std::string> body = splitBySpace(parts[2]);
    std::string result = evaluate(body, lambda_scope);
    exitScope(lambda_scope);
    return result;
}
