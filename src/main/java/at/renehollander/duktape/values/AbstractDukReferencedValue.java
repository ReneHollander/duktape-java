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
        alive = true;
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
            alive = false;
            NativeHelper.unref(this.getParent().getContextPointer(), this.getRef());
        }
    }

    @Override
    protected void finalize() throws Throwable {
        synchronized (getParent()) {
            this.destroy();
        }
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
