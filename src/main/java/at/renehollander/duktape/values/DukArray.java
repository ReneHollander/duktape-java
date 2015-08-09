package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.NativeHelper;

import java.util.AbstractList;

public final class DukArray extends AbstractList<DukValue> implements DukReferencedValue {

    private Duktape parent;
    private int ref;

    public DukArray(Duktape parent) {
        this(parent, createEmptyArray(parent));
    }

    protected DukArray(Duktape parent, int ref) {
        this.parent = parent;
        this.ref = ref;
    }

    @Override
    public Duktape getParent() {
        return parent;
    }

    @Override
    public boolean isArray() {
        return true;
    }

    @Override
    public DukArray asArray() {
        return this;
    }

    @Override
    public native DukValue get(int index);

    @Override
    public native int size();

    public native String toJSON();

    private native static int createEmptyArray(Duktape parent);

    /* ======================================================================== */
    /* =========================== START add(value) =========================== */
    /* ======================================================================== */

    public boolean add(DukValue value) {
        if (value.isNumber()) {
            return add(value.asNumber());
        } else if (value.isBoolean()) {
            return add(value.asBoolean());
        } else if (value.isString()) {
            return add(value.asString());
        } else if (value.isUndefined()) {
            return addUndefined();
        } else if (value.isNull()) {
            return addNull();
        } else if (value.isReferenceValue()) {
            return add(value.asReferencedValue());
        } else {
            throw new WrongValueTypeException("Unknown DukValue");
        }
    }

    public boolean add(double value) {
        this._addDouble(value);
        return true;
    }

    public boolean add(boolean value) {
        this._addBoolean(value);
        return true;
    }

    public boolean add(String value) {
        this._addString(value);
        return true;
    }

    public boolean addUndefined() {
        this._addUndefined();
        return true;
    }

    public boolean addNull() {
        this._addNull();
        return true;
    }

    public boolean add(DukArray value) {
        this._addReference(value.getRef());
        return true;
    }

    public boolean add(DukObject value) {
        this._addReference(value.getRef());
        return true;
    }

    public boolean add(DukFunction value) {
        this._addReference(value.getRef());
        return true;
    }

    public boolean add(AbstractDukReferencedValue value) {
        this._addReference(value.getRef());
        return true;
    }

    private native void _addDouble(double value);

    private native void _addBoolean(boolean value);

    private native void _addString(String value);

    private native void _addUndefined();

    private native void _addNull();

    private native void _addReference(int ref);

    /* ======================================================================== */
    /* =========================== END add(value) ============================= */
    /* ======================================================================== */

    @Override
    public String toString() {
        return toJSON();
    }

    @Override
    public int getRef() {
        return this.ref;
    }

    @Override
    public void destroy() {
        NativeHelper.unref(this.getParent(), this.getRef());
    }

}
