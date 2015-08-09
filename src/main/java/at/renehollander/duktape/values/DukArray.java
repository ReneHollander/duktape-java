package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.NativeHelper;

import java.util.AbstractList;

public final class DukArray extends AbstractList<DukValue> implements DukReferencedValue {

    private Duktape parent;
    private int ref;

    public DukArray(Duktape parent) {
        this(parent, _createArray(parent.getContextPointer()));
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
    public DukValue get(int index) {
        return _get(this.getParent().getContextPointer(), this.getRef(), this.getParent(), index);
    }

    @Override
    public int size() {
        return _size(this.getParent().getContextPointer(), this.getRef());
    }


    public String toJSON() {
        return _toJSON(this.getParent().getContextPointer(), this.getRef());
    }

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
        NativeHelper.unref(this.getParent().getContextPointer(), this.getRef());
    }

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
        _addDouble(this.getParent().getContextPointer(), this.getRef(), value);
        return true;
    }

    public boolean add(boolean value) {
        _addBoolean(this.getParent().getContextPointer(), this.getRef(), value);
        return true;
    }

    public boolean add(String value) {
        _addString(this.getParent().getContextPointer(), this.getRef(), value);
        return true;
    }

    public boolean addUndefined() {
        _addUndefined(this.getParent().getContextPointer(), this.getRef());
        return true;
    }

    public boolean addNull() {
        _addNull(this.getParent().getContextPointer(), this.getRef());
        return true;
    }

    public boolean add(DukArray value) {
        _addReference(this.getParent().getContextPointer(), this.getRef(), value.getRef());
        return true;
    }

    public boolean add(DukObject value) {
        _addReference(this.getParent().getContextPointer(), this.getRef(), value.getRef());
        return true;
    }

    public boolean add(DukFunction value) {
        _addReference(this.getParent().getContextPointer(), this.getRef(), value.getRef());
        return true;
    }

    public boolean add(AbstractDukReferencedValue value) {
        _addReference(this.getParent().getContextPointer(), this.getRef(), value.getRef());
        return true;
    }



    /* ======================================================================== */
    /* =========================== END add(value) ============================= */
    /* ======================================================================== */

    /* ==================================================================== */
    /* ======================== START native calls ======================== */
    /* ==================================================================== */

    private static native int _createArray(long contextPointer);

    public static native int _size(long contextPointer, int objectRef);

    public static native String _toJSON(long contextPointer, int objectRef);

    public static native DukValue _get(long contextPointer, int objectRef, Duktape duktape, int index);

    private static native void _addDouble(long contextPointer, int objectRef, double value);

    private static native void _addBoolean(long contextPointer, int objectRef, boolean value);

    private static native void _addString(long contextPointer, int objectRef, String value);

    private static native void _addUndefined(long contextPointer, int objectRef);

    private static native void _addNull(long contextPointer, int objectRef);

    private static native void _addReference(long contextPointer, int objectRef, int ref);

    /* ==================================================================== */
    /* ========================= END native calls ========================= */
    /* ==================================================================== */

}

