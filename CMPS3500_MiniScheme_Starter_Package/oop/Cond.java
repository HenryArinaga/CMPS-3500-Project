import java.util.List;
import java.util.ArrayList;

public class Cond extends ExpressionHandler{
    public Cond(List<String> expression){
        super(expression, 1);
    }

    public static String handleCond(List<String> expression, Scope scope){
        Cond condExpression = new Cond(expression);

        if(expression.size() < 2){
            return "PARSER_ERROR";
        }

        boolean sawElse = false;

        while(condExpression.index < expression.size()){
            List<String> clause = condExpression.extractPart();

            if(clause.size() < 3 ||
            !clause.get(0).equals("(") ||
            !clause.get(clause.size() - 1).equals(")")){
                return "PARSER_ERROR";
            }

            List<String> parsedClause = new ArrayList<>();

            for(int j = 1; j < clause.size() - 1; j++){
                parsedClause.add(clause.get(j));
            }

            Cond clauseExpression = new Cond(parsedClause);
            clauseExpression.index = 0;
            List<String> testExpr = clauseExpression.extractPart();
            List<String> resultExpr = clauseExpression.extractPart();
        
            if(testExpr.isEmpty() || resultExpr.isEmpty() || clauseExpression.index != expression.size()){
                return "PARSE_ERROR";
            }

            if(testExpr.size() == 1 && testExpr.get(0) == "else"){
                if(sawElse || condExpression.index != expression.size()){
                    return "PARSE_ERROR";
                }

                sawElse = true;
                return Evaluate.evaluate(resultExpr, scope);
            }

            String testValue = Evaluate.evaluate(testExpr, scope);

            if(getError(testValue)){
                return testValue;
            }

            if(testValue == "#t"){
                return Evaluate.evaluate(resultExpr, scope);
            }

            if(testValue == "#f"){
                return "TYPE_MISMATCH";
            }
        }

        return "PARSE_ERROR";
    }
}
