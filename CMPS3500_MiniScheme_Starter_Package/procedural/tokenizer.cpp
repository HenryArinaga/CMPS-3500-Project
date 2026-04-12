/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: tokenizer.cpp                                 /
  / DATE: 03/29/2026                                    /
*/

#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenize(const std::string& source_code) {
    std::vector<std::string> token_list;
    std::string current = "";

    for (char c : source_code) {

        // Option 1: the current character is a PARENTHESIS
        if (c == '(' || c == ')') {

            // Save current token if it exists
            if (!current.empty()) {
                token_list.push_back(current);
                current.clear();
            }

            // Add the parenthesis as its own token
            token_list.push_back(std::string(1, c));
        }

        // Option 2: the current character is just WHITESPACE
        else if (std::isspace(c)) {

            // if you have whitespace, then everything before it
            // should be a single token stored in "current"
            if (!current.empty()) {
                token_list.push_back(current);
                current.clear();
            }
        }

        // Option 3: you have a token that could be one or more
        // characters long. Keep storing those characters in a single
        // token
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