package at.renehollander.duktape;

import at.renehollander.duktape.values.*;

import java.lang.reflect.Method;

public class Main {

    private Duktape duktape;

    public Main() throws Exception {
        System.out.println("Duktape Version " + Duktape.getVersion());

        this.duktape = new Duktape();

        DukValue val = duktape.execute("new Error('i am a error');");
        System.out.println("val: " + val);

        Object method = (Function.TwoArg.WithReturn<DukValue, DukValue, DukValue>) this::lol;
        Class<?> clazz = method.getClass();
        Method invokeMethod = clazz.getMethods()[0];

        DukObject global = duktape.getGlobal();
        global.put("error", new DukError(duktape, DukError.ErrorType.DUK_ERR_TYPE_ERROR, "hurr durr ima type error"));
        System.out.println(global.get("error"));
        DukJavaFunction testMethod = new DukJavaFunction(this.duktape, invokeMethod, method);
        global.put("testMethod", testMethod.getDukFunction());
        global.put("key", "value");
        System.out.println(duktape.getGlobal());
        duktape.execute("function lol() { return 4; }");
        DukValue ret = duktape.getGlobal().get("lol").asFunction().invoke();
        System.out.println("ret: " + ret);
        System.out.println(duktape.getGlobal().get("testMethod").asFunction().invoke(new DukNumber(duktape, 10), new DukNumber(duktape, 11)));
        duktape.execute("testMethod(4, function(v1, v2) { testMethod(v1, key); return 'yay'; });");

        System.out.println(global.get("key"));

        global.remove("testMethod");

        duktape.gc();

        /*
        Class<?> clazz = Main.class;
        Method invokeMethod = clazz.getMethod("lol", int.class, long.class);

        duktape.registerMethod("testMethod", this, invokeMethod, invokeMethod.getParameterCount());
        duktape.execute("testMethod();");

        */
        duktape.destroy();
    }

    public DukValue lol(DukValue v1, DukValue v2) {
        System.out.println("v1=" + v1 + ", v2=" + v2);
        if (v2.isFunction()) {
            DukFunction function = v2.asFunction();
            System.out.println("function invoke: " + function.invoke(new DukString(duktape, "Hello from java through javascript and back to java :D"), new DukNumber(duktape, 2)));
        }
        return new DukNumber(duktape, 5);
    }

    public static void main(String[] args) throws Exception {
        new Main();
    }

}
