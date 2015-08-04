package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukBoolean extends DukValue {

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
}
