package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukFunction extends DukObject {

    protected DukFunction(Duktape parent, int ref) {
        super(parent, ref);
    }

    public DukValue invoke(DukValue... args) {
        return _invoke(this.getParent().getContextPointer(), this.getRef(), args);
    }

    @Override
    public boolean isFunction() {
        return true;
    }

    @Override
    public DukFunction asFunction() {
        return this;
    }

    @Override
    public boolean isObject() {
        return false;
    }

    @Override
    public DukObject asObject() {
        throw new WrongValueTypeException("DukFunction");
    }

    @Override
    public String toString() {
        return "function";
    }

    @Override
    public boolean equals(Object o) {
        // TODO implement
        throw new UnsupportedOperationException("not yet implemented");
    }

    @Override
    public int hashCode() {
        // TODO implement
        throw new UnsupportedOperationException("not yet implemented");
    }

    private static native DukValue _invoke(long contextPointer, int objectRef, DukValue[] arguments);

}
