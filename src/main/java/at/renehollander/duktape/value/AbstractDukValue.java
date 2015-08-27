package at.renehollander.duktape.value;

import at.renehollander.duktape.Duktape;

public abstract class AbstractDukValue implements DukValue {

    private Duktape parent;

    protected AbstractDukValue(Duktape parent) {
        this.parent = parent;
    }

    public Duktape getParent() {
        return parent;
    }

}
