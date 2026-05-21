/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Define.java                                   /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;

public class Define extends ExpressionHandler{
    public Define(List<String> expression){
        super(expression, 2);
    }    

    public static String handleDefine(List<String> expression, Scope scope){
        Define defineExpression = new Define(expression);

        if(expression.size() < 3){
            return "PARSE_ERROR";
        }

        String name = expression.get(1);
        List<String> valueExpression = defineExpression.extractPart();

        if(name.equals("(") ||
            name.equals(")")||
            valueExpression.isEmpty() ||
            defineExpression.index != expression.size()){
                return "PARSE_ERROR";
        }

        if(Recursion.isRecursiveDefinition(valueExpression)){
            return Recursion.handleRecursiveDefine(name, valueExpression, scope);
        }

        String value = Evaluate.evaluate(valueExpression, scope);
        if(getError(value)){
            return value;
        }

        scope.addScopeEntry(name, value);
        return "";
    }
}
