package at.renehollander.duktape;

import at.renehollander.duktape.values.DukObject;

public class Main {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();

        DukObject object1 = new DukObject(duktape);

        duktape.destroy();
    }

}
