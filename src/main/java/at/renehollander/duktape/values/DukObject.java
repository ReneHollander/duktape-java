package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

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

    public native String toJSON();

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

    private native void _putDouble(String key, double value);

    private native void _putBoolean(String key, boolean value);

    private native void _putString(String key, String value);

    private native void _putUndefined(String key);

    private native void _putNull(String key);

    private native void _putReference(String key, int ref);

    @Override
    public int size() {
        // TODO needs implementation
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        return get(key) != null;
    }

    @Override
    public boolean containsValue(Object value) {
        // TODO needs implementation
        return false;
    }

    @Override
    public DukValue get(Object key) {
        // TODO needs implementation
        return null;
    }

    @Override
    public DukValue remove(Object key) {
        // TODO needs implementation
        return null;
    }

    @Override
    public void putAll(Map<? extends String, ? extends DukValue> m) {
        m.forEach(this::put);
    }

    @Override
    public void clear() {
        // TODO needs implementation
    }

    @Override
    public Set<String> keySet() {
        // TODO needs implementation
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

    private native static int createEmptyObject(Duktape parent);

}
