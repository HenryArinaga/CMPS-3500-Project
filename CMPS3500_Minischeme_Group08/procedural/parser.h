/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: parser.h                                      /
  / DATE: 03/29/2026                                    /
*/

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

std::vector<std::string> parseTokens(const std::vector<std::string>& input_tokens);

// Split the tokens into separate expressions
std::vector<std::vector<std::string>> splitExpressions(
    const std::vector<std::string>& tokens
);


#endif
