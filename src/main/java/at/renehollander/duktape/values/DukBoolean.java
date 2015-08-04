package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukBoolean extends DukValue {

    private boolean value;

    public DukBoolean(Duktape parent, boolean value) {
        super(parent);
        this.value = value;
    }

    public boolean getValue() {
        return value;
    }

    public void setValue(boolean value) {
        this.value = value;
    }

    @Override
    public boolean isBoolean() {
        return true;
    }

    @Override
    public boolean asBoolean() {
        return this.value;
    }

    @Override
    public String toString() {
        return Boolean.toString(value);
    }
}
