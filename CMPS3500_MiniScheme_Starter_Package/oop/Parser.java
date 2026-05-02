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
    private List<String> tokens;

    public Parser(List<String> tokens){
        this.tokens = tokens;
    }
    
    public static List<String> parseTokens(List<String> inputTokens){
        List<String> parsedTokens = new ArrayList<>();

        if(inputTokens.isEmpty()){
            return parsedTokens;
        }

        if(inputTokens.get(0).equals("(")){
            if(!inputTokens.get(inputTokens.size() - 1).equals(")")){
                parsedTokens.add("PARSE_ERROR");
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

    public List<List<String>> splitExpressions(){
        List<List<String>> expressions = new ArrayList<>();
        List<String> current = new ArrayList<>();
        int depth = 0;

        for(int i = 0; i < tokens.size(); i++){
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

                if(depth < 0){
                    List<List<String>> parseError = new ArrayList<>();
                    List<String> error = new ArrayList<>();
                    error.add("PARSE_ERROR");
                    parseError.add(error);
                    return parseError;
                }

                if(depth == 0){
                    expressions.add(new ArrayList<>(current));
                }
            }

            if(depth == 0 && !tokens.get(i).equals("(") && !tokens.get(i).equals(")")){
                List<String> single = new ArrayList<>();
                single.add(tokens.get(i));
                expressions.add(single);
            }
        }
        
        if(depth != 0){
            List<List<String>> parseError = new ArrayList<>();
            List<String> error = new ArrayList<>();
            error.add("PARSE_ERROR");
            parseError.add(error);
            return parseError;
        }

        return expressions;
    }
}