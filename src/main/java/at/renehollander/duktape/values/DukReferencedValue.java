package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;

public interface DukReferencedValue extends DukValue, Destroyable {

    public int getRef();

    public void destroy();

}
