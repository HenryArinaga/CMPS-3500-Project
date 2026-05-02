/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Tokenizer.java                                /
  / DATE: 04/11/2026                                    /
*/
import java.util.ArrayList;
import java.util.List;

public class Tokenizer {
    private String sourceCode;

    public Tokenizer(String sourceCode){
        this.sourceCode = sourceCode;
    }

    public List<String> tokenize(){
        List<String> tokenList = new ArrayList<String>();
        String current = "";

        for(char c : sourceCode.toCharArray()){
            if(c == '(' || c == ')'){
                if (!current.isEmpty()){
                    tokenList.add(current);
                    current = "";
                }
                
                tokenList.add(String.valueOf(c));
            }
            else if(Character.isWhitespace(c)){
                if(!current.isEmpty()){
                    tokenList.add(current);
                    current = "";
                }
            }
            else{
                current += c;
            }
        }

        if(!current.isEmpty()){
            tokenList.add(current);
        }

        return tokenList;
    }
}