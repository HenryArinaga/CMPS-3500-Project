/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: parser.cpp                                    /
  / DATE: 03/29/2026                                    /
*/

#include "parser.h"
#include <iostream>

// Handles a single expression
std::vector<std::string> parseTokens(const std::vector<std::string> &input_tokens)
{
    std::vector<std::string> parsed_tokens;

    // Basic check
    if (input_tokens.size() == 0)
    {
        return parsed_tokens;
    }

    // Check for parentheses
    // if it starts with '(' it should end with ')' 
    if (input_tokens[0] == "(")
    {

        if (input_tokens[input_tokens.size() - 1] != ")")
        {
            std::cerr << "Parse error: missing closing parenthesis\n";
            return parsed_tokens;
        }

        // Extract everything inside parentheses
        for (int i = 1; i < (int)input_tokens.size() - 1; i++)
        {
            parsed_tokens.push_back(input_tokens[i]);
        }
    }
    else
    {
        // Single token (like x)
        parsed_tokens.push_back(input_tokens[0]);
    }

    return parsed_tokens;
}

// Splits multiple expressions from token list
std::vector<std::vector<std::string>> splitExpressions(const std::vector<std::string> &tokens)
{
    std::vector<std::vector<std::string>> expressions;
    std::vector<std::string> current;

    int depth = 0;
    int i;

    for (i = 0; i < (int)tokens.size(); i++)
    {

        if (tokens[i] == "(")
        {
            if (depth == 0)
            {
                current.clear();
            }
            depth++;
        }

        if (depth > 0)
        {
            current.push_back(tokens[i]);
        }

        if (tokens[i] == ")")
        {
            depth--;

            if (depth == 0)
            {
                expressions.push_back(current);
            }
        }

        if (depth == 0 && tokens[i] != "(" && tokens[i] != ")")
        {
            std::vector<std::string> single;
            single.push_back(tokens[i]);
            expressions.push_back(single);
        }
    }

    return expressions;
}
