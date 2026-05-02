/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT                                   /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: ExpressionHandler.java                        /
  / DATE: 05/01/2026                                    /
*/

import java.util.List;
import java.util.ArrayList;

public class ExpressionHandler {
    protected List<String> expression;
    protected int index;
    protected int result;
    protected int value;
    protected String error;

    public ExpressionHandler(List<String> expression, int index){
        this.expression = expression;
        this.index = index;
        this.result = 0;
        this.value = 0;
        this.error = "";
    }

    protected List<String> extractPart(){
        List<String> part = new ArrayList<>();
        
        if(index >= expression.size()){
            return part;
        }

        if (!expression.get(index).equals("(")){
            part.add(expression.get(index));
            index++;
            return part;
        }

        int depth = 0;

        while(index < expression.size()){
            part.add(expression.get(index));

            if(expression.get(index).equals("(")){
                depth ++;
            }
            else if(expression.get(index).equals(")")){
                depth--;

                if(depth == 0){
                    index++;
                    break;
                }
            }

            index++;
        }

        return part;
    }

    //idk if this is a good name for this but I saw it was getting
    //reused a lot so I turned it into a method
    protected static boolean getError(String value){
        return value.equals("PARSE_ERROR") ||
            value.equals("UNDECLARED_INDENTIFIER") ||
            value.equals("WRONG_ARITY") ||
            value.equals("TYPE_MISTMATCH") ||
            value.equals("DIVISION_BY_ZERO");
    }
}
