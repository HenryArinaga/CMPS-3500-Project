import java.util.List;
import java.util.ArrayList;

public class If {
    private List<String> expression;
    private int i;

    public If(List<String> expression){
        this.expression = expression;
        this.i = 1;
    }
    
    private List<String> extractIfPart(){
        List<String> part = new ArrayList<>();
        
        if(i >= expression.size()){
            return part;
        }

        if (!expression.get(i).equals("(")){
            part.add(expression.get(i));
            i++;
            return part;
        }

        int depth = 0;

        while(i < expression.size()){
            part.add(expression.get(i));

            if(expression.get(i).equals("(")){
                depth ++;
            }
            else if(expression.get(i).equals(")")){
                depth--;

                if(depth == 0){
                    i++;
                    break;
                }
            }

            i++;
        }

        return part;
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

        List<String> condition = ifExpression.extractIfPart();
        List<String> trueBranch = ifExpression.extractIfPart();
        List<String> falseBranch = ifExpression.extractIfPart();

        if(condition.isEmpty() ||
            trueBranch.isEmpty() ||
            falseBranch.isEmpty() ||
            ifExpression.i != expression.size()){
            return "PARSE_ERROR";
        }

        String condValue = ifExpression.evaluateIfPart(condition, scope);
        
        if(condValue.equals("PARSE_ERROR") ||
            condValue.equals("UNDECLARED_INDENTIFIER") ||
            condValue.equals("WRONG_ARITY") ||
            condValue.equals("TYPE_MISTMATCH") ||
            condValue.equals("DIVISION_BY_ZERO")
        ){
            return condValue;
        }

        if(condValue == "#t"){
            return ifExpression.evaluateIfPart(trueBranch, scope);
        }

        if(condValue == "#f"){
            return ifExpression.evaluateIfPart(falseBranch, scope);
        }

        return "TYPE_MISTMATCH";
    }
}
