#include <iostream>
#include <vector>
#include <string>

std::string eval(const std::string& token); 

void handle_if(const std::vector<std::string>& expr) {

    if (expr.size() != 5) {
        std::cerr << "Error: invalid if expression\n";
        return;
    }

    std::string condition = expr[2];
    std::string true_branch = expr[3];
    std::string false_branch = expr[4];

    std::string result = eval(condition);

    if (result == "#t") {
        std::cout << eval(true_branch) << "\n";
    } else {
        std::cout << eval(false_branch) << "\n";
    }
}