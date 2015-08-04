package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukNull extends DukValue {

    public DukNull(Duktape parent) {
        super(parent);
    }

    @Override
    public boolean isNull() {
        return true;
    }

    @Override
    public DukNull asNull() {
        return null;
    }
}
