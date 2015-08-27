package at.renehollander.duktape.value.object;

import at.renehollander.duktape.value.Destroyable;
import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.value.AbstractDukValue;

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
        super.finalize();
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
