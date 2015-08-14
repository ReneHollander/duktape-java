package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukNull extends AbstractDukValue {

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

    @Override
    public String toString() {
        return null;
    }

    @Override
    public boolean equals(Object obj) {
        return obj == null || obj instanceof DukNull;
    }

    @Override
    public int hashCode() {
        return 0;
    }
}
