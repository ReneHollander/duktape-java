package at.renehollander.duktape;

import at.renehollander.duktape.values.DukObject;

public class Main {

    public static void main(String[] args) {

        System.out.println("Duktape Version " + Duktape.getVersion());

        Duktape duktape = new Duktape();

        DukObject dukObject = new DukObject(duktape);
        DukObject inner = new DukObject(duktape);
        dukObject.put("inner", inner);

        System.out.println(duktape.getRefCount());

        inner.destroy();
        dukObject.destroy();

        inner = null;
        dukObject = null;

        System.gc();
        System.gc();
        System.gc();
        System.gc();
        System.gc();
        System.gc();

        System.out.println(duktape.getRefCount());

        duktape.destroy();
    }

}
