/*
  / NAME: Henry Ariaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: parser.cpp                                    /
  / DATE: 03/29/2026                                    /
*/

#include "parser.h"
#include <iostream>

std::vector<std::string> parseTokens(const std::vector<std::string>& input_tokens) {
    std::vector<std::string> parsed_tokens;

    // Basic check
    if (input_tokens.size() < 3) {
        std::cerr << "Parse error: too few tokens\n";
        return parsed_tokens;
    }

    // Check for parentheses
    if (input_tokens[0] != "(" || input_tokens.back() != ")") {
        std::cerr << "Parse error: missing parentheses\n";
        return parsed_tokens;
    }

    // Extract everything inside parentheses
    for (int i = 0; i < input_tokens.size(); i++) {
        parsed_tokens.push_back(input_tokens[i]);
    }

    return parsed_tokens;
}

