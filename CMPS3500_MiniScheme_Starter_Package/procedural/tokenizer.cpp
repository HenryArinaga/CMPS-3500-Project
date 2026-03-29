#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string current = "";

    for (char c : input) {

        // If we hit a parenthesis
        if (c == '(' || c == ')') {

            // Save current token if it exists
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }

            // Add the parenthesis as its own token
            tokens.push_back(std::string(1, c));
        }

        // hit whitespace
        else if (std::isspace(c)) {

            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        }

        //  keep building the token
        else {
            current += c;
        }
    }

    // Push last token if needed
    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}