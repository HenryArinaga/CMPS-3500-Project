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
    std::string result = "";

    std::string file_path = argv[1];

    std::string source = read_file(file_path);

    auto tokens = tokenize(source);
    auto expressions = splitExpressions(tokens);
    Scope* global = enterScope(NULL);

    int num = 0;
    bool b_num = false;

    for (const auto& expr : expressions)
    {
        result = evaluate(expr, global);

        if (!result.empty())
        {

            std::cout << result << "\n";

            try {
                num = std::stoi(result);
                b_num = true;
            } catch (...) {
                b_num = false;
            }

            if (result == "#t" || result == "#f")
            {
                std::cout << "bool";
            }
            else if (b_num == true)
            {
                std::cout << "int";
            }
            else
            {
                std::cout << "ERROR";
            }
        }
    }

    exitScope(global);
    return 0;
}
