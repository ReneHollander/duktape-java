package at.renehollander.duktape.value;

import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.exception.WrongValueTypeException;
import at.renehollander.duktape.value.object.*;
import at.renehollander.duktape.value.primitive.DukNull;
import at.renehollander.duktape.value.primitive.DukUndefined;

public interface DukValue {

    Duktape getParent();

    default boolean isNumber() {
        return false;
    }

    default double asNumber() {
        throw new WrongValueTypeException("Number");
    }

    default boolean isBoolean() {
        return false;
    }

    default boolean asBoolean() {
        throw new WrongValueTypeException("Boolean");
    }

    default boolean isString() {
        return false;
    }

    default String asString() {
        throw new WrongValueTypeException("String");
    }

    default boolean isObject() {
        return false;
    }

    default DukObject asObject() {
        throw new WrongValueTypeException("Object");
    }

    default boolean isArray() {
        return false;
    }

    default DukArray asArray() {
        throw new WrongValueTypeException("Array");
    }

    default boolean isFunction() {
        return false;
    }

    default DukFunction asFunction() {
        throw new WrongValueTypeException("Function");
    }

    default boolean isUndefined() {
        return false;
    }

    default DukUndefined asUndefined() {
        throw new WrongValueTypeException("Undefined");
    }

    default boolean isNull() {
        return false;
    }

    default DukNull asNull() {
        throw new WrongValueTypeException("Null");
    }

    default boolean isReferenceValue() {
        return false;
    }

    default DukReferencedValue asReferencedValue() {
        throw new WrongValueTypeException("ReferencedValue");
    }

    default boolean isError() {
        return false;
    }

    default DukError asError() {
        throw new WrongValueTypeException("DukError");
    }

    default boolean isBuffer() {
        return false;
    }

    default DukBuffer asBuffer() {
        throw new WrongValueTypeException("DukBuffer");
    }

    @SuppressWarnings("unchecked")
    default <T> T as() {
        return (T) this;
    }

}
