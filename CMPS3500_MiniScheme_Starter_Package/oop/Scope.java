/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: Scope.java                                    /
  / DATE: 04/11/2026                                    /
*/

import java.util.ArrayList;
import java.util.List;

public class Scope {
  private List<ScopeEntry> scopeEntries;
  private Scope parent;

  public Scope(Scope parent){
    this.scopeEntries = new ArrayList<>();
    this.parent = parent;
  }

  public Scope enterScope(){
    return new Scope(this);
  }

  public Scope exitScope(){
    return this.parent;
  }

  public void addScopeEntry(String name, String value){
    this.scopeEntries.add(new ScopeEntry(name, value));
  }

  public String lookupScopeEntry(String name){
    Scope temp = this;

    while(temp != null){
      for(int i = 0; i < temp.scopeEntries.size(); i++){
        if(temp.scopeEntries.get(i).getName().equals(name)){
          return temp.scopeEntries.get(i).getValue();
        }
      }
      temp = temp.parent;
    }

    return "NOT FOUND";
  }

  public boolean existsInCurrentScope(String name){
    for(int i = 0; i < scopeEntries.size(); i++){
      if(scopeEntries.get(i).getName().equals(name)){
        return true;
      }
    }

    return false;
  }
}