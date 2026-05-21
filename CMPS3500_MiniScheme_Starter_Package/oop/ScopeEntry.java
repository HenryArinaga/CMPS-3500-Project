/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga /
  / ASGT: CHECKPOINT 3                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: ScopeEntry.java                               /
  / DATE: 05/01/2026                                    /
*/

public class ScopeEntry {
    private String name;
    private String value;

    public ScopeEntry(String name, String value){
        setName(name);
        setValue(value);
    }

    public String getName() { return name; }
    public String getValue() { return value; }

    public void setName(String name)   { this.name = name; }
    public void setValue(String value){ this.value = value; }
}
