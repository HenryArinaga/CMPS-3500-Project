/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Let.java                                       /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;
import java.util.ArrayList;

public class Let extends ExpressionHandler {
    public Let(List<String> expression){
        super(expression, 1);
    }

    public static String handleLet(List<String> expression, Scope scope){
        Let letExpression = new Let(expression);
        Scope newScope = scope.enterScope();

        if(letExpression.index >= expression.size() || !expression.get(letExpression.index).equals("(")){
            return "PARSE_ERROR";
        }

        letExpression.index++;

        while(letExpression.index < expression.size() && expression.get(letExpression.index).equals("(")){
            letExpression.index++;

            if(letExpression.index >= expression.size()){
                newScope.exitScope();
                return "PARSE_ERROR";
            }

            String var = expression.get(letExpression.index);
            letExpression.index++;

            List<String> valueExpression = letExpression.extractPart();

            if(valueExpression.isEmpty() || letExpression.index >= expression.size()){
                newScope.exitScope();
                return "PARSE_ERROR";
            }

            letExpression.index++;

            String value = Evaluate.evaluate(valueExpression, newScope);

            if(getError(value)){
                newScope.exitScope();
                return "PARSE_ERROR";
            }

            newScope.addScopeEntry(var, value);
        }

        if(letExpression.index >= expression.size() || !expression.get(letExpression.index).equals(")")){
                newScope.exitScope();
                return "PARSE_ERROR";
        }

        letExpression.index++;

        List<String> body = new ArrayList<>();

        while(letExpression.index < expression.size()){
            body.add(expression.get(letExpression.index));
            letExpression.index++;
        }

        String result = Evaluate.evaluate(body, newScope);
        newScope.exitScope();
        return result;
    }
}
