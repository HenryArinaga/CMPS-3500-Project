/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Evaluate.java                                 /
  / DATE: 04/11/2026                                    /
*/

import java.util.List;

public class Evaluate {
  public static String evaluate(List<String> expression, Scope scope){
    if(expression.isEmpty()){
      return "";
    }

    List<String> parsed = Parser.parseTokens(expression);

    if(parsed.isEmpty()){
      return "PARSE_ERROR";
    }

    if(parsed.size() == 1 && parsed.get(0).equals("PARSE_ERROR")){
      return "PARSE_ERROR";
    }

    String op = parsed.get(0);

    if(op.equals("if")){
       return If.handleIf(parsed, scope);
    }
    if(op.equals("define")){
      return Define.handleDefine(parsed, scope);
    }
    if(op.equals("let")){
      return Let.handleLet(parsed, scope);
    }
    if(op.equals("lambda")){
      return Lambda.handleLambda(parsed, scope);
    }
    // if(op.equals("cond")){
    //   return handleCond(parsed, scope);
    // }
    // else{
    //   if(parsed.size() == 1){
    //     if(parsed.get(0).equals("#t" || parsed.get(0).equals"#f")){
    //       return parsed.get(0);
    //     }

    //     boolean isNumber = true;
    //     int start = 0;

    //     if(parsed.get(0).charAt(0) == '-'){
    //       start = 1;
    //     }

    //     for (int i = 0; i< parsed.get(0).length(); i++){
    //       if(parsed.get(0).charAt(i) < '0' || parsed.get(0).charAt(i) > '9' ){
    //         isNumber = false;
    //       }
    //     }

    //     if(isNumber && start < parsed.get(0).length()){
    //       return parsed.get(0);
    //     }

    //     String value = scope.lookupScopeEntry(op){
    //       if(value.equals("NOT FOUND")){
    //         return "UNDECLARED_IDENTIFIER";
    //       }
    //     }

    //     return value;
    //   }
    //   else{
    //     return handleFunctionApplication(parsed, scope);
    //   }
    // }

    return "";
  }
} 