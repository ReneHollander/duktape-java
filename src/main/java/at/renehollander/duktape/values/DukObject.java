package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.NativeHelper;

import java.util.*;

public final class DukObject extends AbstractMap<String, DukValue> implements DukReferencedValue, Destroyable {

    private Duktape parent;
    private int ref;

    private Set<Map.Entry<String, DukValue>> entrySet;

    public DukObject(Duktape parent) {
        this(parent, createObject(parent.getContextPointer()));
    }

    protected DukObject(Duktape parent, int ref) {
        this.parent = parent;
        this.ref = ref;
    }

    @Override
    public Duktape getParent() {
        return this.parent;
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

    public DukValue put(String key, DukReferencedValue value) {
        DukValue old = this.get(key);
        _putReference(this.getParent().getContextPointer(), this.getRef(), key, value.getRef());
        return old;
    }

    @Override
    public boolean containsKey(Object key) {
        return key instanceof String && _containsKey(this.getParent().getContextPointer(), this.getRef(), (String) key);
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

    @Override
    public Set<Entry<String, DukValue>> entrySet() {
        if (entrySet == null) entrySet = new DukObjectEntrySet();
        return this.entrySet;
    }


    public String toJSON() {
        return _toJSON(this.getParent().getContextPointer(), this.getRef());
    }

    @Override
    public int getRef() {
        return this.ref;
    }

    @Override
    public void destroy() {
        NativeHelper.unref(this.getParent().getContextPointer(), this.getRef());
    }

    public class DukObjectEntrySet extends AbstractSet<Map.Entry<String, DukValue>> {

        @Override
        public boolean add(Entry<String, DukValue> stringDukValueEntry) {
            return DukObject.this.put(stringDukValueEntry.getKey(), stringDukValueEntry.getValue()) == null;
        }

        @Override
        public Iterator<Entry<String, DukValue>> iterator() {
            return new DukObjectEntrySetIterator();
        }

        @Override
        public int size() {
            return DukObject.this.size();
        }

        public class DukObjectEntrySetIterator implements Iterator<Map.Entry<String, DukValue>> {

            @Override
            public boolean hasNext() {
                //TODO needs impl
                return false;
            }

            @Override
            public Entry<String, DukValue> next() {
                //TODO needs impl
                return null;
            }

            @Override
            public void remove() {
                //TODO needs impl
            }
        }
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
