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
    std::string status = "OK";
    std::string type = "auto";

    // ----This was used to test our reader for checkpoint 1 using
    // ----the command line. Checkpoint 2 should use run_all.sh
    if (argc != 2)
    {
        std::cout << "Usage: ./test <file_name>\n";
        return 1;
    }

    std::string file_path = std::string("./tests/public/") + argv[1];

    // ---- whole process starts here ----

    // Step 1: Get source code from file.
    std::string source = read_file(file_path);

    // Step 2: turn that source code into TOKENS
    auto tokens = tokenize(source);

    // Step 3: Turn tokens into separate expressions.
    //         each expression has a depth level, and
    //         it can have one or multiple tokens
    auto expressions = splitExpressions(tokens);
    //                 splitExpressions() is found in parser.cpp

    //Step 4: Deal with SCOPE
    // Start by defining global scope
    Scope* global = enterScope(NULL);

    // Step 5: EVALUATE every expression found in the list of epxressions
    for (const auto& expr : expressions)
    {
        result = evaluate(expr, global);

        if (!result.empty())
        {
            //std::cout << argv[1] << " -> Status: " << status << 
            //" | Result: " << result << " | Type: " << type << "\n";
            std::cout << result << "\n";
            if (result == "#t" || result == "#f")
            {
                std::cout << "Type: bool" << "\n";
            }
            else 
            {
                std::cout << "Type: int";
            }
        }
    }

    exitScope(global);
    return 0;
}
