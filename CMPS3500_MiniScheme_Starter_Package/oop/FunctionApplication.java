/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: FunctionApplication.java                      /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;
import java.util.ArrayList;

public class FunctionApplication extends ExpressionHandler {
    public FunctionApplication(List<String> expression){
        super(expression, 1);
    }

    private static boolean isIntegerLiteral(String token){
        if(token.isEmpty()){
            return false;
        }

        int start = 0;

        if(token.charAt(0) == '-'){
            if(token.length() == 1){
                return false;
            }

            start = 1;
        }

        for(int i = start; i < token.length(); i++){
            if(!Character.isDigit(token.charAt(i))){
                return false;
            }
        }

        return true;
    }

    private boolean resolveValue(
        String token,
        Scope scope
    ){
        String value = token;

        if(!isIntegerLiteral(value)){
            if(value.equals("#t") || value.equals("#f")){
                this.error = "TYPE_MISMATCH";
                return false;
            }

            value = scope.lookupScopeEntry(value);

            if(value.equals("NOT FOUND")){
                this.error = "UNDECLARED_IDENTIFIER";
                return false;
            }

            if(!isIntegerLiteral(value)){
                this.error = "TYPE_MISMATCH";
                return false;
            }
        }

        this.value = Integer.parseInt(value);
        return true;
    }

    private boolean resolveExpressionValue(
        Scope scope
    ){
        if(!expression.get(index).equals("(")){
            if(!resolveValue(expression.get(index), scope)){
                return false;
            }

            index++;
            return true;
        }

        List<String> nestedExpression = extractPart();
        String value = Evaluate.evaluate(nestedExpression, scope);
        
        if(getError(value)){
            this.error = value;
            return false;
        }

        if(!isIntegerLiteral(value)){
            this.error = "TYPE_MISMATCH";
            return false;
        }

        this.value = Integer.parseInt(value);
        return true;
    }

    public static String handleFunctionApplication(
        List<String> expression,
        Scope scope
    ){
        String op = expression.get(0);

        if(op.equals("(")){
            FunctionApplication faExp = new FunctionApplication(expression);
            faExp.index = 0;
            List<String> lambdaExpr = faExp.extractPart();
            List<List<String>> arguments = new ArrayList<>();

            while(faExp.index < expression.size()){
                arguments.add(faExp.extractPart());
            }

            String lambdaValue = Evaluate.evaluate(lambdaExpr, scope);

            if(getError(lambdaValue)){
                return lambdaValue;
            }

            return Lambda.applyLambdaValue(lambdaValue, arguments, scope);
        }

        String lambdaValue = scope.lookupScopeEntry(op);

        if(Lambda.isLambdaValue(lambdaValue)){
            FunctionApplication faExp = new FunctionApplication(expression);
            List<List<String>> arguments = new ArrayList<>();

            while(faExp.index < expression.size()){
                arguments.add(faExp.extractPart());
            }

            return Lambda.applyLambdaValue(lambdaValue, arguments, scope);
        }

        if (op.equals("+")) {
            FunctionApplication faExp = new FunctionApplication(expression);

            while (faExp.index < expression.size()) {
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                faExp.result += faExp.value;
            }

            return Integer.toString(faExp.result);
        } 
        else if (op.equals("-")) {
            FunctionApplication faExp = new FunctionApplication(expression);

            if (expression.size() < 2) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }
                
                faExp.result -= faExp.value;
            }

            return Integer.toString(faExp.result);
        }
        else if (op.equals("*")) {
            FunctionApplication faExp = new FunctionApplication(expression);
            faExp.result = 1;

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }
                
                faExp.result *= faExp.value;
            }

            return Integer.toString(faExp.result);
        }
        else if (op.equals("/")) {
            FunctionApplication faExp = new FunctionApplication(expression);

            if (expression.size() < 2) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                if (faExp.value == 0)
                {
                    return "DIVISION_BY_ZERO";
                }
                
                faExp.result /= faExp.value;
            }

            return Integer.toString(faExp.result);
        }
        else if (op.equals("=")) {
            FunctionApplication faExp = new FunctionApplication(expression);
            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            int left = faExp.value;

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                int right = faExp.value;

                if (left != right)
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals("<")) {
            FunctionApplication faExp = new FunctionApplication(expression);

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            int left = faExp.value;

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                int right = faExp.value;

                if (!(left < right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals(">")) {
            FunctionApplication faExp = new FunctionApplication(expression);

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            int left = faExp.value;

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                int right = faExp.value;

                if (!(left > right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals("<=")) {
            FunctionApplication faExp = new FunctionApplication(expression);
            
            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            int left = faExp.value;

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                int right = faExp.value;

                if (!(left <= right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals(">=")) {
            FunctionApplication faExp = new FunctionApplication(expression);
            
            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!faExp.resolveExpressionValue(scope)) {
                return faExp.error;
            }

            int left = faExp.value;

            while(faExp.index < expression.size()){
                if (!faExp.resolveExpressionValue(scope)) {
                    return faExp.error;
                }

                int right = faExp.value;

                if (!(left >= right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }

        return "UNDECLARED_IDENTIFIER";
    }     
}
