package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukBoolean extends AbstractDukValue {

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
        return this.getValue();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Boolean) {
            return (boolean) o == this.getValue();
        } else
            return o instanceof DukBoolean && ((DukBoolean) o).getValue() == this.getValue();
    }

    @Override
    public int hashCode() {
        return (getValue() ? 1 : 0);
    }

    @Override
    public String toString() {
        return Boolean.toString(getValue());
    }
}
