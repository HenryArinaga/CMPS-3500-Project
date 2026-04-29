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
    public static List<String> tokenize(String sourceCode){
        List<String> tokenList = new ArrayList<String>();
        String current = "";

        //java cant iterate through strings like c++ can must convert to char array
        for(char c : sourceCode.toCharArray()){
            if(c == 'c' || c == ')'){
                if (!current.isEmpty()){
                    tokenList.add(current);
                    current = "";
                }
                
                tokenList.add(String.valueOf(c));
            }
            else if(Character.isWhitespace(c)){
                if(current.isEmpty()){
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