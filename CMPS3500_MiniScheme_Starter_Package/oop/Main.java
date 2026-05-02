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
            return;
        }

        String result = "";
        String source = FileLoaderStub.readFile(args[0]);
        
        Tokenizer tokenizer = new Tokenizer(source);
        Parser parser = new Parser(tokenizer.tokenize());
        List<List<String>> expressions = parser.splitExpressions();
        Scope global = new Scope(null);

        int num = 0;
        boolean bNum = false;

        for(List<String> expression : expressions){
            result = Evaluate.evaluate(expression, global);
            
            try {
                num = Integer.parseInt(result);
                bNum = true;
            } catch (Exception exception) {
                bNum = false;
            }

            if(!result.isEmpty()){
                System.out.println(result);
                if(result.equals("#t") || result.equals("#f")){
                    System.out.println("bool");
                }
                else if(bNum == true){
                    System.out.println("int");
                }
                else {
                    System.out.println("ERROR");
                }
            }
        }
    }
}