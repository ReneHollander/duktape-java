package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class Creator {

    protected native static int createEmptyObject(Duktape parent);

    protected native static int createEmptyArray(Duktape parent);

}
