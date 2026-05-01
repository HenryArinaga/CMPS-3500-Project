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
