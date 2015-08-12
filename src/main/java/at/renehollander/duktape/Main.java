package at.renehollander.duktape;

import at.renehollander.duktape.values.DukObject;

import java.lang.reflect.Method;

public class Main {

    public Main() throws Exception {
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


        Object method = (Function.TwoArg.WithoutReturn<Integer, Long>) this::lol;
        Class<?> clazz = method.getClass();
        Method invokeMethod = clazz.getMethods()[0];

        duktape.registerMethod("testMethod", method, invokeMethod, invokeMethod.getParameterCount());
        duktape.execute("testMethod();");


        /*
        Class<?> clazz = Main.class;
        Method invokeMethod = clazz.getMethod("lol", int.class, long.class);

        duktape.registerMethod("testMethod", this, invokeMethod, invokeMethod.getParameterCount());
        duktape.execute("testMethod();");

        duktape.destroy();
        */
    }

    public void lol(int i, long l) {
        System.out.println("i=" + i + ", l=" + l);
    }

    public static void main(String[] args) throws Exception {
        new Main();
    }

}
