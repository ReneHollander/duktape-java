package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukFunction extends AbstractDukReferencedValue {

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
    public String toString() {
        return "function";
    }

    private static native DukValue _invoke(long contextPointer, int objectRef, DukValue[] arguments);

}
