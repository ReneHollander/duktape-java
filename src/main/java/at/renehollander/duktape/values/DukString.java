package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukString extends AbstractDukValue {

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

    @Override
    public String toString() {
        return value;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        DukString dukString = (DukString) o;

        return !(value != null ? !value.equals(dukString.value) : dukString.value != null);

    }

    @Override
    public int hashCode() {
        return value != null ? value.hashCode() : 0;
    }
}
