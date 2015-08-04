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
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
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
    public boolean add(DukValue value) {
        return false;
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
    public DukValue get(int index) {
        return null;
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

    private native static int createEmptyArray(Duktape parent);

}
