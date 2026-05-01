/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Main.java                                     /
  / DATE: 04/11/2026                                    /
*/

import java.util.List;

public class Main{
    public static void main(String[] args) throws Exception {
        if(args.length != 1){
            System.out.println("Usage: ./miniscm <file_name>");
            return;
        }

        String result = "";
        String source = FileLoaderStub.readFile(args[0]);
        
        Tokenizer tokenizer = new Tokenizer(source);
        Parser parser = new Parser(tokenizer.tokenize());
        List<List<String>> expressions = parser.splitExpressions();
        Scope global = new Scope(null);

        for(List<String> expression : expressions){
            result = Evaluate.evaluate(expression, global);
            
            if(!result.isEmpty()){
                System.out.println(result);
                if(result.equals("#t") || result.equals("#f")){
                    System.out.println("bool");
                }
                else {
                    System.out.println("int");
                }
            }
        }
    }
}