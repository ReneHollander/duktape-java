package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;

public abstract class DukReferencedValue extends DukValue implements Destroyable {

    private int ref;

    protected DukReferencedValue(Duktape parent, int ref) {
        super(parent);
        this.ref = ref;
    }

    public int getRef() {
        return ref;
    }

    public void destroy() {
        this.unref();
    }

    @Override
    public boolean isReferenceValue() {
        return true;
    }

    @Override
    public DukReferencedValue asReferencedValue() {
        return this;
    }

    private native void unref();

}
