package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public class DukError extends AbstractDukValue {

    private DukValue errorObject;

    protected DukError(Duktape parent, DukValue errorObject) {
        super(parent);
        this.errorObject = errorObject;
    }

    public DukValue getErrorObject() {
        return errorObject;
    }

    @Override
    public boolean isError() {
        return true;
    }

    @Override
    public DukError asError() {
        return this;
    }
}
