package at.renehollander.duktape.value.object;

import at.renehollander.duktape.value.Destroyable;
import at.renehollander.duktape.util.NativeHelper;
import at.renehollander.duktape.value.DukValue;

public interface DukReferencedValue extends DukValue, Destroyable {

    int getRef();

    boolean isAlive();

    void setAlive(boolean alive);

    default void destroy() {
        if (isAlive()) {
            setAlive(false);
            NativeHelper.unref(this);
        }
    }

    default void markForDestroy() {
        if (isAlive()) {
            setAlive(false);
            NativeHelper.mark_for_unref(this);
        }
    }

}
