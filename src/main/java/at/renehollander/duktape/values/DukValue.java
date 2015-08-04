package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public abstract class DukValue {

    private Duktape parent;

    public DukValue(Duktape parent) {
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

    public <T> T as() {
        return (T) this;
    }


}
