/*
  / NAME: Henry Ariaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: main.cpp                                      /
  / DATE: 03/29/2026                                    /
*/

#include "tokenizer.h"
#include "parser.h"
#include "scope.h"
#include "evaluate.h"
#include <iostream>
#include <string>


std::string read_file(const std::string& path);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./test <file_name>\n";
        return 1;
    }

    std::string file_path = std::string("../tests/public/") + argv[1];

    std::string source = read_file(file_path);

    auto tokens = tokenize(source);
    auto expressions = splitExpressions(tokens);

    Scope* global = enterScope(NULL);

    for (const auto& expr : expressions)
    {
        evaluate(expr, global);
    }

    exitScope(global);
    return 0;
}
