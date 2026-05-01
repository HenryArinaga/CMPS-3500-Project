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
            defineExpression.i != expression.size()){
                return "PARSE_ERROR";
        }

        // if(isRecursiveDefinition(valueExpression)){
        //     return handleRecursiveDefine(name, valueExpression, scope);
        // }

        String value = Evaluate.evaluate(valueExpression, scope);
        if(getError(value)){
            return value;
        }

        scope.addScopeEntry(name, value);
        return "";
    }
}
