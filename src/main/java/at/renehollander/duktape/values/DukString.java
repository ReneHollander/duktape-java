package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukString extends DukValue {

    private String value;

    public DukString(Duktape parent) {
        super(parent);
    }

    @Override
    public boolean isString() {
        return true;
    }

    @Override
    public String asString() {
        return value;
    }
}
