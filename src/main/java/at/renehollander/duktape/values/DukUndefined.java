package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukUndefined extends AbstractDukValue {

    public DukUndefined(Duktape parent) {
        super(parent);
    }

    @Override
    public boolean isUndefined() {
        return true;
    }

    @Override
    public DukUndefined asUndefined() {
        return this;
    }

    @Override
    public String toString() {
        return "undefined";
    }
}
