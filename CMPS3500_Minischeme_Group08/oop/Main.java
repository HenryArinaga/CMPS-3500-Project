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

        String source = FileLoaderStub.readFile(args[0]);
        
        List<String> tokens = Tokenizer.tokenize(source);
        List<List<String>> expressions = Parser.splitExpressions(tokens);

        for(List<String> expression : expressions){
            List<String> parsed = Parser.parseTokens(expression);

            System.out.println("Expression: " + expression);
            System.out.println("Parsed:     " + parsed);
        }
        
    }
}