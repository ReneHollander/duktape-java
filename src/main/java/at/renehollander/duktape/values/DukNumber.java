package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukNumber extends DukValue {

    private double value;

    public DukNumber(Duktape parent) {
        super(parent);
    }

    @Override
    public boolean isNumber() {
        return true;
    }

    @Override
    public double asNumber() {
        return value;
    }

}
