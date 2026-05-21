/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: If.java                                       /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;

public class If extends ExpressionHandler {
    public If(List<String> expression){
        super(expression, 1);
    }

    private String evaluateIfPart(List<String> part, Scope scope){
        if(part.isEmpty()){
            return "";
        }
        
        if(part.size() == 1 && (part.get(0).equals("#t") || part.get(0).equals("#f"))){
            return part.get(0);
        }

        return Evaluate.evaluate(part, scope);
    }

    public static String handleIf(List<String> expression, Scope scope){
        If ifExpression = new If(expression);

        List<String> condition = ifExpression.extractPart();
        List<String> trueBranch = ifExpression.extractPart();
        List<String> falseBranch = ifExpression.extractPart();

        if(condition.isEmpty() ||
            trueBranch.isEmpty() ||
            falseBranch.isEmpty() ||
            ifExpression.index != expression.size()){
            return "PARSE_ERROR";
        }

        String value = ifExpression.evaluateIfPart(condition, scope);
        
        if(getError(value)){
            return value;
        }

        if(value == "#t"){
            return ifExpression.evaluateIfPart(trueBranch, scope);
        }

        if(value == "#f"){
            return ifExpression.evaluateIfPart(falseBranch, scope);
        }

        return "TYPE_MISTMATCH";
    }
}
