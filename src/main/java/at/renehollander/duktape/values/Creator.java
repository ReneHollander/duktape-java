package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

public final class Creator {

    protected static int createEmptyObject(Duktape parent) {
        return 0;
    }

    protected static int createEmptyArray(Duktape parent) {
        return 0;
    }

}
