package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukNumber extends DukValue {

    private double value;

    public DukNumber(Duktape parent, double value) {
        super(parent);
        this.value = value;
    }

    public double getValue() {
        return value;
    }

    public void setValue(double value) {
        this.value = value;
    }

    @Override
    public boolean isNumber() {
        return true;
    }

    @Override
    public double asNumber() {
        return value;
    }

    @Override
    public String toString() {
        return Double.toString(value);
    }
}
