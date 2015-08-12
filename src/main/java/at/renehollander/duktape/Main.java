package at.renehollander.duktape;

import at.renehollander.duktape.values.DukFunction;
import at.renehollander.duktape.values.DukNumber;
import at.renehollander.duktape.values.DukString;
import at.renehollander.duktape.values.DukValue;

import java.lang.reflect.Method;

public class Main {

    private Duktape duktape;

    public Main() throws Exception {
        System.out.println("Duktape Version " + Duktape.getVersion());

        this.duktape = new Duktape();

        Object method = (Function.TwoArg.WithoutReturn<DukValue, DukValue>) this::lol;
        Class<?> clazz = method.getClass();
        Method invokeMethod = clazz.getMethods()[0];

        duktape.registerMethod("testMethod", method, invokeMethod, invokeMethod.getParameterCount());
        duktape.execute("testMethod(4, function(v1, v2) { testMethod(v1, v2); });");


        /*
        Class<?> clazz = Main.class;
        Method invokeMethod = clazz.getMethod("lol", int.class, long.class);

        duktape.registerMethod("testMethod", this, invokeMethod, invokeMethod.getParameterCount());
        duktape.execute("testMethod();");

        duktape.destroy();
        */
    }

    public void lol(DukValue v1, DukValue v2) {
        System.out.println("v1=" + v1 + ", v2=" + v2);
        if (v2.isFunction()) {
            DukFunction function = v2.asFunction();
            function.invoke(new DukString(duktape, "Hello from java through javascript and back to java :D"), new DukNumber(duktape, 2));
        }
    }

    public static void main(String[] args) throws Exception {
        new Main();
    }

}
