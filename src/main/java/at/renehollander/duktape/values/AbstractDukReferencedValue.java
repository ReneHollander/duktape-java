package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;

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
    public void setAlive(boolean alive) {
        this.alive = alive;
    }

    @Override
    protected void finalize() throws Throwable {
        this.markForDestroy();
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
