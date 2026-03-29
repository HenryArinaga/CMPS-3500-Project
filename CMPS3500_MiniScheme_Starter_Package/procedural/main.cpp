#include "tokenizer.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

std::string read_file(const std::string& path);

int main() {
    std::string code = read_file("../tests/public/addon_03.scm");

    std::vector<std::string> tokens = tokenize(code);
    std::vector<std::string> parsed = parse(tokens);

    std::cout << "Parsed result:\n";
    for (const auto& t : parsed) {
        std::cout << t << "\n";
    }

    return 0;
}