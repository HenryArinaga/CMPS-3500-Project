/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Recursion.java                                /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;

public class Recursion {
    public static boolean isRecursiveDefinition(List<String> valueExpr){
        return !valueExpr.isEmpty() &&
        valueExpr.get(0).equals("(") &&
        valueExpr.size() > 1 &&
        valueExpr.get(1) == "lambda";
    }

    public static String handleRecursiveDefine(
        String name,
        List<String> valueExpr,
        Scope scope
    ){
        String value = Evaluate.evaluate(valueExpr, scope);
        scope.addScopeEntry(name, value);
        return "";
    }
}
