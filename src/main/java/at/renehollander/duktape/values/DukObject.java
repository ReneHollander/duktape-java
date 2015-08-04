package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public class DukObject extends DukReferencedValue implements Map<String, DukValue> {

    public DukObject(Duktape parent, int ref) {
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

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean containsKey(Object key) {
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        return false;
    }

    @Override
    public DukValue get(Object key) {
        return null;
    }

    @Override
    public DukValue put(String key, DukValue value) {
        return null;
    }

    @Override
    public DukValue remove(Object key) {
        return null;
    }

    @Override
    public void putAll(Map<? extends String, ? extends DukValue> m) {

    }

    @Override
    public void clear() {

    }

    @Override
    public Set<String> keySet() {
        return null;
    }

    @Override
    public Collection<DukValue> values() {
        return null;
    }

    @Override
    public Set<Entry<String, DukValue>> entrySet() {
        return null;
    }
}
