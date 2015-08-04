package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukFunction extends DukReferencedValue {

    public DukFunction(Duktape parent, int ref) {
        super(parent, ref);
    }

    public void invoke(Object... args) {

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
