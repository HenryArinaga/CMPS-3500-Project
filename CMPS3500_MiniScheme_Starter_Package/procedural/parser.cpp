#include "parser.h"
#include <iostream>

std::vector<std::string> parse(const std::vector<std::string>& tokens) {
    std::vector<std::string> result;

    // Basic check
    if (tokens.size() < 3) {
        std::cerr << "Parse error: too few tokens\n";
        return result;
    }

    // Expect format: ( something ... )
    if (tokens[0] != "(" || tokens.back() != ")") {
        std::cerr << "Parse error: missing parentheses\n";
        return result;
    }

    // Extract everything inside parentheses
    for (size_t i = 0; i < tokens.size(); i++) {
        result.push_back(tokens[i]);
    }

    return result;
}

