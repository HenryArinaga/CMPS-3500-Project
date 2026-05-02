/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: FunctionApplication.java                    /
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

    private static boolean resolveValue(
        String token,
        Scope scope,
        int result,
        String error
    ){
        String value = token;

        if(!isIntegerLiteral(value)){
            if(value.equals("#t") || value.equals("#f")){
                error = "TYPE_MISMATCH";
                return false;
            }

            value = scope.lookupScopeEntry(value);

            if(value == "NOT FOUND"){
                error = "UNDECLARED_IDENTIFIER";
                return false;
            }

            if(!isIntegerLiteral(value)){
                error = "TYPE_MISMATCH";
                return false;
            }
        }

        result = Integer.parseInt(value);
        return true;
    }

    private boolean resolveExpressionValue(
        Scope scope,
        int result,
        String error
    ){
        if(!expression.get(index).equals("(")){
            if(!resolveValue(expression.get(index), scope, result, error)){
                return false;
            }

            index++;
            return true;
        }

        List<String> nestedExpression = extractPart();

        String value = Evaluate.evaluate(nestedExpression, scope);
        
        if(getError(value)){
            error = value;
            return false;
        }

        if(!isIntegerLiteral(value)){
            error = "TYPE_MISMATCH";
            return false;
        }

        result = Integer.parseInt(value);
        return true;
    }

    public static String handleFunctionApplication(
        List<String> expression,
        Scope scope
    ){
        String op = expression.get(0);

        if(op.equals("(")){
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            funcAppExpression.index = 0;
            List<String> lambdaExpr = funcAppExpression.extractPart();
            List<List<String>> arguments = new ArrayList<>();

            while(funcAppExpression.index < expression.size()){
                arguments.add(funcAppExpression.extractPart());
            }

            String lambdaValue = Evaluate.evaluate(lambdaExpr, scope);

            if(getError(lambdaValue)){
                return lambdaValue;
            }

            return Lambda.applyLambdaValue(lambdaValue, arguments, scope);
        }

        String lambdaValue = scope.lookupScopeEntry(op);

        if(Lambda.isLambdaValue(lambdaValue)){
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            List<List<String>> arguments = new ArrayList<>();

            while(funcAppExpression.index < expression.size()){
                arguments.add(funcAppExpression.extractPart());
            }

            return Lambda.applyLambdaValue(lambdaValue, arguments, scope);
        }

        if (op.equals("+")) {
            int result = 0;
            FunctionApplication funcAppExpression = new FunctionApplication(expression);

            while (funcAppExpression.index < expression.size()) {
                int value = 0;
                String error = "";

                if (!funcAppExpression.resolveExpressionValue( scope, value, error)) {
                    return error;
                }

                result += value;
            }

            return Integer.toString(result);
        } 
        else if (op.equals("-")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            String error = "";
            int result = 0;
            
            if (expression.size() < 2) {
                return "WRONG_ARITY";
            }

            if (!funcAppExpression.resolveExpressionValue( scope, result, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
            int value = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, value, error)) {
                    return error;
                }
                
                result -= value;
            }

            return Integer.toString(result);
        }
        else if (op.equals("*")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int result = 1;

            while(funcAppExpression.index < expression.size()){
                int value = 0;
                String error = "";

                if (!funcAppExpression.resolveExpressionValue( scope, value, error)) {
                    return error;
                }
                
                result *= value;
            }

            return Integer.toString(result);
        }
        else if (op.equals("/")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int result = 0;
            String error = "";

            if (expression.size() < 2) {
                return "WRONG_ARITY";
            }
            if (!funcAppExpression.resolveExpressionValue( scope, result, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
                int value = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, value, error)) {
                    return error;
                }

                if (value == 0)
                {
                    return "DIVISION_BY_ZERO";
                }
                
                result /= value;
            }

            return Integer.toString(result);
        }
        else if (op.equals("=")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int left = 0;
            String error = "";

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!funcAppExpression.resolveExpressionValue( scope, left, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
                int right = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, right, error)) {
                    return error;
                }

                if (left != right)
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals("<")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int left = 0;
            String error = "";

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!funcAppExpression.resolveExpressionValue( scope, left, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
                int right = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, right, error)) {
                    return error;
                }

                if (!(left < right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals(">")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int left = 0;
            String error = "";

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!funcAppExpression.resolveExpressionValue( scope, left, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
                int right = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, right, error)) {
                    return error;
                }

                if (!(left > right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals("<=")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int left = 0;
            String error = "";

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!funcAppExpression.resolveExpressionValue( scope, left, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
                int right = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, right, error)) {
                    return error;
                }

                if (!(left <= right))
                {
                    return "#f";
                }
                
                left = right;
            }

            return "#t";
        }
        else if (op.equals(">=")) {
            FunctionApplication funcAppExpression = new FunctionApplication(expression);
            int left = 0;
            String error = "";

            if (expression.size() < 3) {
                return "WRONG_ARITY";
            }

            if (!funcAppExpression.resolveExpressionValue( scope, left, error)) {
                return error;
            }

            while(funcAppExpression.index < expression.size()){
                int right = 0;

                if (!funcAppExpression.resolveExpressionValue( scope, right, error)) {
                    return error;
                }

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
    
