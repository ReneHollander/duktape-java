package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukFunction extends DukReferencedValue {

    protected DukFunction(Duktape parent, int ref) {
        super(parent, ref);
    }

    public void invoke(DukValue... args) {

    }

    @Override
    public boolean isFunction() {
        return true;
    }

    @Override
    public DukFunction asFunction() {
        return this;
    }
}
