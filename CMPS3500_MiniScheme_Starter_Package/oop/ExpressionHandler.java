import java.util.List;
import java.util.ArrayList;

public class ExpressionHandler {
    protected List<String> expression;
    protected int i;

    public ExpressionHandler(List<String> expression, int index){
        this.expression = expression;
        this.i = index;
    }

    protected List<String> extractPart(){
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
