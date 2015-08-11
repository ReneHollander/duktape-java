package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.NativeHelper;

public abstract class AbstractDukReferencedValue extends AbstractDukValue implements DukReferencedValue, Destroyable {

    private int ref;

    protected AbstractDukReferencedValue(Duktape parent, int ref) {
        super(parent);
        this.ref = ref;
    }

    public int getRef() {
        return ref;
    }

    public void destroy() {
        NativeHelper.unref(this.getParent().getContextPointer(), this.getRef());
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
