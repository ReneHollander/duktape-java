package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukString extends DukValue {

    private String value;

    public DukString(Duktape parent, String value) {
        super(parent);
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
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
