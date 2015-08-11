package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public interface DukValue {

    public Duktape getParent();

    public default boolean isNumber() {
        return false;
    }

    public default double asNumber() {
        throw new WrongValueTypeException("Number");
    }

    public default boolean isBoolean() {
        return false;
    }

    public default boolean asBoolean() {
        throw new WrongValueTypeException("Boolean");
    }

    public default boolean isString() {
        return false;
    }

    public default String asString() {
        throw new WrongValueTypeException("String");
    }

    public default boolean isObject() {
        return false;
    }

    public default DukObject asObject() {
        throw new WrongValueTypeException("Object");
    }

    public default boolean isArray() {
        return false;
    }

    public default DukArray asArray() {
        throw new WrongValueTypeException("Array");
    }

    public default boolean isFunction() {
        return false;
    }

    public default DukFunction asFunction() {
        throw new WrongValueTypeException("Function");
    }

    public default boolean isUndefined() {
        return false;
    }

    public default DukUndefined asUndefined() {
        throw new WrongValueTypeException("Undefined");
    }

    public default boolean isNull() {
        return false;
    }

    public default DukNull asNull() {
        throw new WrongValueTypeException("Null");
    }

    public default boolean isReferenceValue() {
        return false;
    }

    public default DukReferencedValue asReferencedValue() {
        throw new WrongValueTypeException("ReferencedValue");
    }

    public default <T> T as() {
        return (T) this;
    }

}
