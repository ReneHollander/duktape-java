package at.renehollander.duktape.value.primitive;

import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.value.AbstractDukValue;

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

    @Override
    public boolean equals(Object obj) {
        return obj instanceof DukUndefined;
    }

    @Override
    public int hashCode() {
        return 1;
    }
}
