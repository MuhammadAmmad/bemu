package BEmu.HistoricalDataRequest;

import BEmu.Name;

public class ElementHistoricDouble extends ElementParent
{
	private final double _value;
	private final String _name;
	
	ElementHistoricDouble(String name, double value)
	{
		this._name = name;
		this._value = value;
	}
	
    public Name name()
    {
    	return new Name(this._name);
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean isComplexType()
    {
    	return false;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return super.prettyPrintHelper(tabIndent, String.valueOf(this._value));
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public double getValueAsFloat64()
    {
        return this._value;
    }
    
    public int getValueAsInt32()
    {
        return (int)this._value;
    }
    
    public long getValueAsInt64()
    {
        return (long)this._value;
    }
    
    public String getValueAsString()
    {
        return String.valueOf(this._value);
    }
}