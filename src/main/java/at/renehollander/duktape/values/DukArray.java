package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

public final class DukArray extends DukReferencedValue implements List<DukValue> {

    public DukArray(Duktape parent) {
        super(parent, createEmptyArray(parent));
    }

    protected DukArray(Duktape parent, int ref) {
        super(parent, ref);
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

    public boolean add(DukReferencedValue value) {
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
    public native int size();

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public Iterator<DukValue> iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return null;
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends DukValue> c) {
        return false;
    }

    @Override
    public boolean addAll(int index, Collection<? extends DukValue> c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return false;
    }

    @Override
    public void clear() {

    }


    @Override
    public DukValue set(int index, DukValue element) {
        return null;
    }

    @Override
    public void add(int index, DukValue element) {
    }

    @Override
    public DukValue remove(int index) {
        return null;
    }

    @Override
    public int indexOf(Object o) {
        return 0;
    }

    @Override
    public int lastIndexOf(Object o) {
        return 0;
    }

    @Override
    public ListIterator<DukValue> listIterator() {
        return null;
    }

    @Override
    public ListIterator<DukValue> listIterator(int index) {
        return null;
    }

    @Override
    public List<DukValue> subList(int fromIndex, int toIndex) {
        return null;
    }

    @Override
    public String toString() {
        return toJSON();
    }

    public native String toJSON();

    private native static int createEmptyArray(Duktape parent);

}
