package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public abstract class DukValue {

    private Duktape parent;

    public DukValue(Duktape parent) {
        this.parent = parent;
    }

    public Duktape getParent() {
        return parent;
    }
}
