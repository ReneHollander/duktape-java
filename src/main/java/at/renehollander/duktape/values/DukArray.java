package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.NativeHelper;

import java.util.AbstractList;

public final class DukArray extends AbstractList<DukValue> implements DukReferencedValue {

    private Duktape parent;
    private int ref;
    private boolean alive;

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
    public boolean isReferenceValue() {
        return true;
    }

    @Override
    public DukReferencedValue asReferencedValue() {
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
    public boolean isAlive() {
        return alive;
    }

    @Override
    public void destroy() {
        if (isAlive()) {
            NativeHelper.unref(this.getParent().getContextPointer(), this.getRef());
            alive = false;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        this.destroy();
    }

    @Override
    public DukValue remove(int index) {
        DukValue old = this.get(index);
        _remove(this.getParent().getContextPointer(), this.getRef(), index);
        return old;
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

    public boolean add(DukReferencedValue value) {
        _addReference(this.getParent().getContextPointer(), this.getRef(), value.getRef());
        return true;
    }

    /* ======================================================================== */
    /* =========================== END add(value) ============================= */
    /* ======================================================================== */

    /* ======================================================================== */
    /* ======================== START add(index value) ======================== */
    /* ======================================================================== */

    public void add(int index, DukValue value) {
        if (value.isNumber()) {
            add(index, value.asNumber());
        } else if (value.isBoolean()) {
            add(index, value.asBoolean());
        } else if (value.isString()) {
            add(index, value.asString());
        } else if (value.isUndefined()) {
            addUndefined(index);
        } else if (value.isNull()) {
            addNull(index);
        } else if (value.isReferenceValue()) {
            add(index, value.asReferencedValue());
        } else {
            throw new WrongValueTypeException("Unknown DukValue");
        }
    }

    public void add(int index, double value) {
        _addDouble(this.getParent().getContextPointer(), this.getRef(), index, value);
    }

    public void add(int index, boolean value) {
        _addBoolean(this.getParent().getContextPointer(), this.getRef(), index, value);
    }

    public void add(int index, String value) {
        _addString(this.getParent().getContextPointer(), this.getRef(), index, value);
    }

    public void addUndefined(int index) {
        _addUndefined(this.getParent().getContextPointer(), this.getRef(), index);
    }

    public void addNull(int index) {
        _addNull(this.getParent().getContextPointer(), this.getRef(), index);
    }

    public void add(int index, DukReferencedValue value) {
        _addReference(this.getParent().getContextPointer(), this.getRef(), index, value.getRef());
    }

    /* ======================================================================== */
    /* ========================= END add(index value) ========================= */
    /* ======================================================================== */

    /* ======================================================================== */
    /* ======================== START set(index value) ======================== */
    /* ======================================================================== */

    public DukValue set(int index, DukValue value) {
        if (value.isNumber()) {
            return set(index, value.asNumber());
        } else if (value.isBoolean()) {
            return set(index, value.asBoolean());
        } else if (value.isString()) {
            return set(index, value.asString());
        } else if (value.isUndefined()) {
            return setUndefined(index);
        } else if (value.isNull()) {
            return setNull(index);
        } else if (value.isReferenceValue()) {
            return set(index, value.asReferencedValue());
        } else {
            throw new WrongValueTypeException("Unknown DukValue");
        }
    }

    public DukValue set(int index, double value) {
        DukValue old = this.get(index);
        _setDouble(this.getParent().getContextPointer(), this.getRef(), index, value);
        return old;
    }

    public DukValue set(int index, boolean value) {
        DukValue old = this.get(index);
        _setBoolean(this.getParent().getContextPointer(), this.getRef(), index, value);
        return old;
    }

    public DukValue set(int index, String value) {
        DukValue old = this.get(index);
        _setString(this.getParent().getContextPointer(), this.getRef(), index, value);
        return old;
    }

    public DukValue setUndefined(int index) {
        DukValue old = this.get(index);
        _setUndefined(this.getParent().getContextPointer(), this.getRef(), index);
        return old;
    }

    public DukValue setNull(int index) {
        DukValue old = this.get(index);
        _setNull(this.getParent().getContextPointer(), this.getRef(), index);
        return old;
    }

    public DukValue set(int index, DukReferencedValue value) {
        DukValue old = this.get(index);
        _setReference(this.getParent().getContextPointer(), this.getRef(), index, value.getRef());
        return old;
    }

    /* ======================================================================== */
    /* ========================= END set(index value) ========================= */
    /* ======================================================================== */

    /* ======================================================================== */
    /* ========================== START native calls ========================== */
    /* ======================================================================== */

    private static native int _createArray(long contextPointer);

    public static native int _size(long contextPointer, int objectRef);

    public static native String _toJSON(long contextPointer, int objectRef);

    public static native DukValue _get(long contextPointer, int objectRef, Duktape duktape, int index);

    public static native void _remove(long contextPointer, int objectRef, int index);

    // START add(value)

    private static native void _addDouble(long contextPointer, int objectRef, double value);

    private static native void _addBoolean(long contextPointer, int objectRef, boolean value);

    private static native void _addString(long contextPointer, int objectRef, String value);

    private static native void _addUndefined(long contextPointer, int objectRef);

    private static native void _addNull(long contextPointer, int objectRef);

    private static native void _addReference(long contextPointer, int objectRef, int ref);

    // END add(value)

    // START add(index value)

    private static native void _addDouble(long contextPointer, int objectRef, int index, double value);

    private static native void _addBoolean(long contextPointer, int objectRef, int index, boolean value);

    private static native void _addString(long contextPointer, int objectRef, int index, String value);

    private static native void _addUndefined(long contextPointer, int objectRef, int index);

    private static native void _addNull(long contextPointer, int objectRef, int index);

    private static native void _addReference(long contextPointer, int objectRef, int ref, int index);

    // END add(index value)

    // START set(index value)

    private static native void _setDouble(long contextPointer, int objectRef, int index, double value);

    private static native void _setBoolean(long contextPointer, int objectRef, int index, boolean value);

    private static native void _setString(long contextPointer, int objectRef, int index, String value);

    private static native void _setUndefined(long contextPointer, int objectRef, int index);

    private static native void _setNull(long contextPointer, int objectRef, int index);

    private static native void _setReference(long contextPointer, int objectRef, int ref, int index);

    // END set(index value)

    /* ======================================================================== */
    /* =========================== END native calls =========================== */
    /* ======================================================================== */

}

