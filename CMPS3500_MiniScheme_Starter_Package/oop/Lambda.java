/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Lambda.java                                       /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;
import java.util.ArrayList;

public class Lambda extends ExpressionHandler {
    public Lambda(List<String> expression){
        super(expression, 2);
    }

    private static String joinTokens(List<String> tokens, int start, int end){
        String result = ""; 

        for(int i = start; i < end; i++){
            if(!result.isEmpty()){
                result += " ";
            }
            result += tokens.get(i);
        }

        return result;
    }

    private static List<String> splitString(String text, char delimiter){
        List<String> parts = new ArrayList<>();
        String current = "";

        for(int i = 0; i < text.length(); i++){
            if(text.charAt(i) == delimiter){
                parts.add(current);
                current = "";
            }
            else{
                current += text.charAt(i);
            }
        }

        parts.add(current);
        return parts;
    }

    private static List<String> spliteBySpace(String text){
        List<String> tokens = new ArrayList<>();
        String current = "";

        for(int i = 0; i < text.length(); i++){
            if(text.charAt(i) == ' '){
                if(!current.isEmpty()){
                    tokens.add(current);
                    current = "";
                }
            }
            else{
                current += text.charAt(i);
            }
        }

        if(!current.isEmpty()){
            tokens.add(current);
        }

        return tokens;
    }

    public static String handleLambda(List<String> expression, Scope scope){
        Lambda lambdaExpression = new Lambda(expression);

        if(expression.size() < 5){
            return "PARSE_ERROR";
        }

        if(!expression.get(1).equals("(")){
            return "PARSE_ERROR";
        }

        List<String> params = new ArrayList<>();

        while(lambdaExpression.index < expression.size() && !expression.get(lambdaExpression.index).equals(")")){
            if(expression.get(lambdaExpression.index).equals("(")){
                return "PARSE_ERROR";
            }

            params.add(expression.get(lambdaExpression.index));
            lambdaExpression.index++;
        }

        if(lambdaExpression.index >= expression.size() || !expression.get(lambdaExpression.index).equals(lambdaExpression)){
            return "PARSE_ERROR";
        }

        lambdaExpression.index++;

        if(lambdaExpression.index >= expression.size()){
            return "PARSE_ERROR";
        }

        String paramText = "";

        for(int j = 0; j < params.size(); j++){
            if(!paramText.isEmpty()){
                paramText += ",";
            }

            paramText += params.get(j);
        }

        String bodyText = joinTokens(expression, lambdaExpression.index, expression.size());

        if(bodyText.isEmpty()){
            return "PARSE_ERROR";
        }

        return "LAMBDA|" + paramText + "|" + bodyText;
    }

    public static boolean isLambdaValue(String value){
        return value.length() >= 7 && value.substring(0,7).equals("LAMBDA|");
    }

    public static String applyLambdaValue(String lambdaValue, List<List<String>> arguments, Scope scope){
        if(!isLambdaValue(lambdaValue)){
            return "TYPE_MISMATCH";
        }

        List<String> parts = splitString(lambdaValue, '|');

        if(parts.size() != 3){
            return "TYPE_MISMATCH";
        }

        List<String> params = new ArrayList<>();

        if(!parts.get(1).isEmpty()){
            params = splitString(lambdaValue, ',');
        }

        if(params.size() != arguments.size()){
            return "WRONG_ARITY";
        }

        Scope lambdaScope = scope.enterScope();

        for(int i = 0; i < params.size(); i++){
            String value = Evaluate.evaluate(arguments.get(i), scope);
            if(getError(value)){
                lambdaScope.exitScope();
                return value;
            }
            
            lambdaScope.addScopeEntry(params.get(i), value);
        }

        List<String> body = spliteBySpace(parts.get(2));
        String result = Evaluate.evaluate(body, lambdaScope);
        lambdaScope.exitScope();
        return result;
    }
}
