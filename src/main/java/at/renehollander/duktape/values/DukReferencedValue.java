package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.NativeHelper;

public interface DukReferencedValue extends DukValue, Destroyable {

    public int getRef();

    public boolean isAlive();

    public void setAlive(boolean alive);

    public default void destroy() {
        if (isAlive()) {
            setAlive(false);
            NativeHelper.unref(this);
        }
    }

    public default void markForDestroy() {
        if (isAlive()) {
            setAlive(false);
            System.out.println("mark for destroy");
            NativeHelper.mark_for_unref(this);
        }
    }

}
