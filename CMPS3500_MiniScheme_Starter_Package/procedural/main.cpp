/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: main.cpp                                      /
  / DATE: 03/29/2026
*/

#include "tokenizer.h"
#include "parser.h"
#include "scope.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

std::string read_file(const std::string &path);

// check if string is a number
bool is_number(const std::string &s)
{
    int i;
    for (i = 0; i < (int)s.size(); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./<program_name> <file_name>\n";
        return 0;
    }

    std::string file_location = std::string("../tests/public/") + argv[1];
    std::string source_code = read_file(file_location);

    std::vector<std::string> token_list = tokenize(source_code);
    std::vector<std::vector<std::string> > expressions = split_expressions(token_list);

    // create global scope
    Scope *current_scope = enter_scope(NULL);

    int i;
    for (i = 0; i < (int)expressions.size(); i++)
    {
        std::vector<std::string> parsed = parseTokens(expressions[i]);

        if (parsed.size() == 0)
        {
            continue;
        }

        // Handle define and variable assignment
        if (parsed[0] == "define")
        {
            if (parsed.size() >= 3)
            {
                std::string name = parsed[1];
                std::string value = parsed[2];

                add_binding(current_scope, name, value);
                std::cout << "Defined: " << name << " = " << value << "\n";
            }
        }
        else
        {
            std::string op = parsed[0];

            // IF expression
            if (op == "if")
            {
                if (parsed.size() == 4)
                {
                    std::string condition = parsed[1];
                    std::string true_branch = parsed[2];
                    std::string false_branch = parsed[3];

                    std::string cond_value;

                    // resolve condition
                    if (condition == "#t" || condition == "#f")
                    {
                        cond_value = condition;
                    }
                    else
                    {
                        cond_value = lookup_binding(current_scope, condition);
                    }

                    if (cond_value == "#t")
                    {
                        std::cout << true_branch << "\n";
                    }
                    else
                    {
                        std::cout << false_branch << "\n";
                    }
                }
                else
                {
                    std::cout << "Error: invalid if expression\n";
                }

                continue;
            }

            // Arithmetic or variable lookup
            if (parsed.size() == 3)
            {
                std::string left = parsed[1];
                std::string right = parsed[2];

                int a;
                int b;

                if (is_number(left))
                {
                    a = std::stoi(left);
                }
                else
                {
                    std::string val = lookup_binding(current_scope, left);
                    a = std::stoi(val);
                }

                if (is_number(right))
                {
                    b = std::stoi(right);
                }
                else
                {
                    std::string val = lookup_binding(current_scope, right);
                    b = std::stoi(val);
                }

                if (op == "+")
                {
                    std::cout << (a + b) << "\n";
                }
                else if (op == "-")
                {
                    std::cout << (a - b) << "\n";
                }
                else if (op == "*")
                {
                    std::cout << (a * b) << "\n";
                }
                else if (op == "/")
                {
                    std::cout << (a / b) << "\n";
                }
                else
                {
                    std::cout << "Unknown operator: " << op << "\n";
                }
            }
            else
            {
                // variable lookup
                std::string value = lookup_binding(current_scope, parsed[0]);
                std::cout << parsed[0] << " = " << value << "\n";
            }
        }
    }

    current_scope = exit_scope(current_scope);

    return 0;
}