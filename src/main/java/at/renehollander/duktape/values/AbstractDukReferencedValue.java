package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.NativeHelper;

public abstract class AbstractDukReferencedValue extends AbstractDukValue implements DukReferencedValue, Destroyable {

    private int ref;
    private boolean alive;

    protected AbstractDukReferencedValue(Duktape parent, int ref) {
        super(parent);
        this.ref = ref;
    }

    public int getRef() {
        return ref;
    }

    @Override
    public boolean isAlive() {
        return alive;
    }

    @Override
    public void destroy() {
        if (isAlive()) {
            NativeHelper.unref(this.getParent().getContextPointer(), this.getRef());
            alive = false;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        this.destroy();
    }

    @Override
    public boolean isReferenceValue() {
        return true;
    }

    @Override
    public DukReferencedValue asReferencedValue() {
        return this;
    }
}
