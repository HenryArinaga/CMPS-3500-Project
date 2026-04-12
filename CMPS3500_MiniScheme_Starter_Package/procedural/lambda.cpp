/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: lambda.cpp                                    /
  / DATE: 04/11/2026                                    /
*/
#include "lambda.h"
#include <string>
#include <vector>

// Handles the lambda expression and returns a
// encoded string representing the lambda function
std::string handleLambda(const std::vector<std::string>& expr, Scope* scope)
{
    int i = 1;

    if (expr[i] != "(") return "ERROR";
    i++;

    std::vector<std::string> params;

    while (expr[i] != ")")
    {
        params.push_back(expr[i]);
        i++;
    }

    i++;

    std::vector<std::string> body;

    while (i < (int)expr.size())
    {
        body.push_back(expr[i]);
        i++;
    }

    std::string encoded = "LAMBDA:";

    for (auto& p : params)
    {
        encoded += p + ",";
    }

    encoded += ":";

    for (auto& b : body)
    {
        encoded += b + " ";
    }

    return encoded;
}
