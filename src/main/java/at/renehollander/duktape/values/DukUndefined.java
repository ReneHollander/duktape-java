package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukUndefined extends DukValue {

    public DukUndefined(Duktape parent) {
        super(parent);
    }

    @Override
    public boolean isUndefined() {
        return true;
    }

    @Override
    public DukUndefined asUndefined() {
        return this;
    }

}
