package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public final class DukObject extends AbstractDukReferencedValue implements Map<String, DukValue> {

    public DukObject(Duktape parent) {
        super(parent, createObject(parent.getContextPointer()));
    }

    protected DukObject(Duktape parent, int ref) {
        super(parent, ref);
    }

    @Override
    public boolean isObject() {
        return true;
    }

    @Override
    public DukObject asObject() {
        return this;
    }

    public DukValue put(String key, DukValue value) {
        if (value.isNumber()) {
            return put(key, value.asNumber());
        } else if (value.isBoolean()) {
            return put(key, value.asBoolean());
        } else if (value.isString()) {
            return put(key, value.asString());
        } else if (value.isUndefined()) {
            return putUndefined(key);
        } else if (value.isNull()) {
            return putNull(key);
        } else if (value.isReferenceValue()) {
            return put(key, value.asReferencedValue());
        } else {
            throw new WrongValueTypeException("Unknown DukValue");
        }
    }

    public DukValue put(String key, double value) {
        DukValue old = this.get(key);
        _putDouble(this.getParent().getContextPointer(), this.getRef(), key, value);
        return old;
    }

    public DukValue put(String key, boolean value) {
        DukValue old = this.get(key);
        _putBoolean(this.getParent().getContextPointer(), this.getRef(), key, value);
        return old;
    }

    public DukValue put(String key, String value) {
        DukValue old = this.get(key);
        _putString(this.getParent().getContextPointer(), this.getRef(), key, value);
        return old;
    }

    public DukValue putUndefined(String key) {
        DukValue old = this.get(key);
        _putUndefined(this.getParent().getContextPointer(), this.getRef(), key);
        return old;
    }

    public DukValue putNull(String key) {
        DukValue old = this.get(key);
        _putNull(this.getParent().getContextPointer(), this.getRef(), key);
        return old;
    }

    public DukValue put(String key, DukArray value) {
        DukValue old = this.get(key);
        _putReference(this.getParent().getContextPointer(), this.getRef(), key, value.getRef());
        return old;
    }

    public DukValue put(String key, DukObject value) {
        DukValue old = this.get(key);
        _putReference(this.getParent().getContextPointer(), this.getRef(), key, value.getRef());
        return old;
    }

    public DukValue put(String key, DukFunction value) {
        DukValue old = this.get(key);
        _putReference(this.getParent().getContextPointer(), this.getRef(), key, value.getRef());
        return old;
    }

    public DukValue put(String key, AbstractDukReferencedValue value) {
        DukValue old = this.get(key);
        _putReference(this.getParent().getContextPointer(), this.getRef(), key, value.getRef());
        return old;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        return key instanceof String && _containsKey(this.getParent().getContextPointer(), this.getRef(), (String) key);
    }

    @Override
    public boolean containsValue(Object value) {
        if (!(value instanceof DukValue)) {
            return false;
        }
        // TODO needs implementation
        return false;
    }

    @Override
    public DukValue get(Object key) {
        if (!(key instanceof String)) {
            return new DukUndefined(this.getParent());
        }
        return _get(this.getParent().getContextPointer(), this.getRef(), this.getParent(), (String) key);
    }


    @Override
    public DukValue remove(Object key) {
        if (!(key instanceof String)) return new DukUndefined(this.getParent());
        DukValue oldValue = get(key);
        if (oldValue == null) {
            return new DukUndefined(this.getParent());
        } else {
            _remove(this.getParent().getContextPointer(), this.getRef(), (String) key);
            return oldValue;
        }
    }

    @Override
    public void putAll(Map<? extends String, ? extends DukValue> m) {
        m.forEach(this::put);
    }

    @Override
    public Set<String> keySet() {
        // TODO needs implementation
        new HashSet<String>();
        return null;
    }

    @Override
    public Collection<DukValue> values() {
        // TODO needs implementation
        return null;
    }

    @Override
    public Set<Entry<String, DukValue>> entrySet() {
        // TODO needs implementation
        return null;
    }

    @Override
    public String toString() {
        return this.toJSON();
    }

    @Override
    public int size() {
        return _size(this.getParent().getContextPointer(), this.getRef());
    }


    @Override
    public void clear() {
        _clear(this.getParent().getContextPointer(), this.getRef());
    }


    public String toJSON() {
        return _toJSON(this.getParent().getContextPointer(), this.getRef());
    }

    private static native int createObject(long contextPointer);

    private static native int _size(long contextPointer, int objectRef);

    private static native void _clear(long contextPointer, int objectRef);

    private static native String _toJSON(long contextPointer, int objectRef);

    private static native boolean _containsKey(long contextPointer, int objectRef, String key);

    private static native DukValue _get(long contextPointer, int objectRef, Duktape duktape, String key);

    private static native void _remove(long contextPointer, int objectRef, String key);

    private static native void _putDouble(long contextPointer, int objectRef, String key, double value);

    private static native void _putBoolean(long contextPointer, int objectRef, String key, boolean value);

    private static native void _putString(long contextPointer, int objectRef, String key, String value);

    private static native void _putUndefined(long contextPointer, int objectRef, String key);

    private static native void _putNull(long contextPointer, int objectRef, String key);

    private static native void _putReference(long contextPointer, int objectRef, String key, int ref);


}
