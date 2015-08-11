package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public abstract class AbstractDukValue implements DukValue {

    private Duktape parent;

    protected AbstractDukValue(Duktape parent) {
        this.parent = parent;
    }

    public Duktape getParent() {
        return parent;
    }

    public boolean isNumber() {
        return false;
    }

    public double asNumber() {
        throw new WrongValueTypeException("Number");
    }

    public boolean isBoolean() {
        return false;
    }

    public boolean asBoolean() {
        throw new WrongValueTypeException("Boolean");
    }

    public boolean isString() {
        return false;
    }

    public String asString() {
        throw new WrongValueTypeException("String");
    }

    public boolean isObject() {
        return false;
    }

    public DukObject asObject() {
        throw new WrongValueTypeException("Object");
    }

    public boolean isArray() {
        return false;
    }

    public DukArray asArray() {
        throw new WrongValueTypeException("Array");
    }

    public boolean isFunction() {
        return false;
    }

    public DukFunction asFunction() {
        throw new WrongValueTypeException("Function");
    }

    public boolean isUndefined() {
        return false;
    }

    public DukUndefined asUndefined() {
        throw new WrongValueTypeException("Undefined");
    }

    public boolean isNull() {
        return false;
    }

    public DukNull asNull() {
        throw new WrongValueTypeException("Null");
    }

    public boolean isReferenceValue() {
        return false;
    }

    public DukReferencedValue asReferencedValue() {
        throw new WrongValueTypeException("ReferencedValue");
    }

    public <T> T as() {
        return (T) this;
    }

}
