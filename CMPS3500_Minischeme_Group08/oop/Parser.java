/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Parser.java                                   /
  / DATE: 04/11/2026                                    /
*/

import java.util.ArrayList;
import java.util.List;

public class Parser {
    public static List<String> parseTokens(List<String> inputTokens){
        List<String> parsedTokens = new ArrayList<>();

        if(inputTokens.isEmpty()){
            return parsedTokens;
        }

        if(inputTokens.get(0).equals("(")){
            if(inputTokens.get(inputTokens.size() - 1).equals(")")){
                System.err.println("Parse error: missing closing parenthesis");
                return parsedTokens;
            }
            for(int i = 1; i < inputTokens.size() - 1; i++){
                parsedTokens.add(inputTokens.get(i));
            }
        }
        else{
            parsedTokens.add(inputTokens.get(0));
        }

        return parsedTokens;
    }

    public static List<List<String>> splitExpressions(List<String> tokens){
        List<List<String>> expressions = new ArrayList<>();
        List<String> current = new ArrayList<>();
        int depth = 0;
        int i;

        for(i = 0; i < tokens.size(); i++){
            if(tokens.get(i).equals("(")){
                if(depth == 0){
                    current.clear();
                }
                depth++;
            }

            if(depth > 0){
                current.add(tokens.get(i));
            }

            if(tokens.get(i).equals(")")){
                depth--;

                if(depth == 0){
                    expressions.add(current);
                }
            }

            if(depth == 0 && !tokens.get(i).equals("(") && !tokens.get(i).equals(")")){
                List<String> single = new ArrayList<>();
                single.add(tokens.get(i));
                expressions.add(single);
            }
        }
        
        return expressions;
    }
}