package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class DukNumber extends AbstractDukValue {

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
        return this.getValue();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Double) {
            return Double.compare((Double) o, this.getValue()) == 0;
        } else
            return o instanceof DukNumber && Double.compare(((DukNumber) o).getValue(), this.getValue()) == 0;
    }


    @Override
    public int hashCode() {
        long temp = Double.doubleToLongBits(this.getValue());
        return (int) (temp ^ (temp >>> 32));
    }

    @Override
    public String toString() {
        return Double.toString(this.getValue());
    }
}
