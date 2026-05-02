/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 3                                   /
  / ORGN: CSUB - CMPS 3500                               /
  / FILE: cond.cpp                                       /
  / DATE: 05/1/2026                                      / 
*/

#include "cond.h"
#include "evaluate.h"

// function to extract a part of the expression, 
// which can be either a single token or a parenthesized sub-expression
static std::vector<std::string> extractPart(
    const std::vector<std::string>& expr,
    int& i
)
{
    std::vector<std::string> part_of_expr;

    // check if end of expression reached
    // size is cast to int to avoid signed/unsigned comparison warning
    if (i >= (int)expr.size())
    {
        return part_of_expr;
    }

    // if the current token is not an opening parenthesis, 
    // return it as a single token part
    if (expr[i] != "(")
    {   
        // take the current character from expr and add it onto part
        part_of_expr.push_back(expr[i]);
        i++;
        return part_of_expr;
    }

    int depth = 0;

    // while there are more tokens in the expression, 
    // keep adding them to part until matching closing parenthesis are found
    while (i < (int)expr.size())
    {
        part_of_expr.push_back(expr[i]);

        if (expr[i] == "(")
        {
            depth++;
        }
        else if (expr[i] == ")")
        {
            depth--;

            if (depth == 0) // if depth is 0, matching closing parenthesis found, 
                            // so break out of the loop
            {
                i++;
                break;
            }
        }

        i++;
    }

    return part_of_expr;
}

// function to handle the cond special form
std::string handleCond(const std::vector<std::string>& expr, Scope* scope)
{
    // check for at least 2 tokens
    if (expr.size() < 2)
    {
        return "PARSE_ERROR";
    }

    int i = 1;
    bool else_seen = false;

    // loop through the clauses in the cond expression, 
    // extracting each clause and evaluating its test expression
    while (i < (int)expr.size())
    {   
        // returns string vector of the clause, 
        // which is either a single token or a parenthesized sub-expression
        std::vector<std::string> clause = extractPart(expr, i);
        
        // check for at least 3 tokens and starts with ( and ends with )
        if (clause.size() < 3 || clause[0] != "(" || clause[clause.size() - 1] != ")")
        {
            return "PARSE_ERROR";
        }

        // copy the clause without its opening and closing parentheses
        std::vector<std::string> parsed_clause;

        for (int j = 1; j < (int)clause.size() - 1; j++)
        {
            parsed_clause.push_back(clause[j]);
        }

        // extract the test expression and result expression from the parsed clause
        int clause_index = 0;
        std::vector<std::string> test_expr = extractPart(parsed_clause, clause_index);
        std::vector<std::string> result_expr = extractPart(parsed_clause, clause_index);

        if (test_expr.empty() || 
            result_expr.empty() || 
            clause_index != (int)parsed_clause.size())
        {
            return "PARSE_ERROR";
        }

        // if the test expression is "else", check for validity and 
        // evaluate the result expression
        if (test_expr.size() == 1 && test_expr[0] == "else")
        {
            if (else_seen || i != (int)expr.size())
            {
                return "PARSE_ERROR";
            }

            else_seen = true;
            // if the test expression is "else", 
            // evaluate the result expression and return its value
            return evaluate(result_expr, scope);
        }

        // evaluate the test expression and check for errors
        std::string test_value = evaluate(test_expr, scope);

        if (test_value == "PARSE_ERROR" ||
            test_value == "UNDECLARED_IDENTIFIER" ||
            test_value == "WRONG_ARITY" ||
            test_value == "TYPE_MISMATCH" ||
            test_value == "DIVISION_BY_ZERO")
        {
            return test_value;
        }
        
        // checks for true or false depending on the value of the test expression
        if (test_value == "#t")
        {
            return evaluate(result_expr, scope);
        }

        if (test_value != "#f")
        {
            return "TYPE_MISMATCH";
        }
    }

    return "PARSE_ERROR";
}
