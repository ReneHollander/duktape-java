package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.*;

public final class DukObject extends DukReferencedValue implements Map<String, DukValue> {

    public DukObject(Duktape parent) {
        super(parent, createEmptyObject(parent));
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
        this._putDouble(key, value);
        return old;
    }

    public DukValue put(String key, boolean value) {
        DukValue old = this.get(key);
        this._putBoolean(key, value);
        return old;
    }

    public DukValue put(String key, String value) {
        DukValue old = this.get(key);
        this._putString(key, value);
        return old;
    }

    public DukValue putUndefined(String key) {
        DukValue old = this.get(key);
        this._putUndefined(key);
        return old;
    }

    public DukValue putNull(String key) {
        DukValue old = this.get(key);
        this._putNull(key);
        return old;
    }

    public DukValue put(String key, DukArray value) {
        DukValue old = this.get(key);
        this._putReference(key, value.getRef());
        return old;
    }

    public DukValue put(String key, DukObject value) {
        DukValue old = this.get(key);
        this._putReference(key, value.getRef());
        return old;
    }

    public DukValue put(String key, DukFunction value) {
        DukValue old = this.get(key);
        this._putReference(key, value.getRef());
        return old;
    }

    public DukValue put(String key, DukReferencedValue value) {
        DukValue old = this.get(key);
        this._putReference(key, value.getRef());
        return old;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        return key instanceof String && _containsKey((String) key);
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
        return _get((String) key);
    }


    @Override
    public DukValue remove(Object key) {
        if (!(key instanceof String)) return new DukUndefined(this.getParent());
        DukValue oldValue = get(key);
        if (oldValue == null) {
            return new DukUndefined(this.getParent());
        } else {
            this._remove((String) key);
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
    public native int size();

    @Override
    public native void clear();

    public native String toJSON();

    private native boolean _containsKey(String key);

    private native DukValue _get(String key);

    private native void _remove(String key);

    private native void _putDouble(String key, double value);

    private native void _putBoolean(String key, boolean value);

    private native void _putString(String key, String value);

    private native void _putUndefined(String key);

    private native void _putNull(String key);

    private native void _putReference(String key, int ref);

    private native static int createEmptyObject(Duktape parent);

}
