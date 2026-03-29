#include "tokenizer.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

std::string read_file(const std::string& path);

int main() {
    // Example of using the file loader, tokenizer, and parser together
    std::string source_code = read_file("../tests/public/addon_03.scm");

    std::vector<std::string> token_list = tokenizeSource(source_code);
    std::vector<std::string> parsed_expression = parseTokens(token_list);

    std::cout << "Parsed result:\n";
    for (const auto& t : parsed_expression) {
        std::cout << t << "\n";
    }

    return 0;
}