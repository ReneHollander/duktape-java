package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public abstract class DukReferencedValue extends DukValue {

    private int ref;

    protected DukReferencedValue(Duktape parent, int ref) {
        super(parent);
    }

    public int getRef() {
        return ref;
    }

    public void unref() {
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        this.unref();
    }
}
