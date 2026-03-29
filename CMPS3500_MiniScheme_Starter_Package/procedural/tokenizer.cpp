#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenize(const std::string& source_code) {
    std::vector<std::string> token_list;
    std::string current = "";

    for (char c : source_code) {

        // If we hit a parenthesis
        if (c == '(' || c == ')') {

            // Save current token if it exists
            if (!current.empty()) {
                token_list.push_back(current);
                current.clear();
            }

            // Add the parenthesis as its own token
            token_list.push_back(std::string(1, c));
        }

        // hit whitespace
        else if (std::isspace(c)) {

            if (!current.empty()) {
                token_list.push_back(current);
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
        token_list.push_back(current);
    }

    return token_list;
}