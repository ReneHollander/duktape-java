package at.renehollander.duktape;

import at.renehollander.duktape.values.*;

import java.lang.reflect.Method;

public class Main {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();
        System.out.println("Initial Memory Usage: " + duktape.getHeapUsage());

        DukArray innerArray = new DukArray(duktape);

        DukObject innerObject = new DukObject(duktape);
        innerObject.put("heyo", "captain jack");

        DukObject object = new DukObject(duktape);
        object.put("numberValue", 10);
        object.put("stringValue", "lol");
        object.put("stringValue", "fag");
        object.putUndefined("undefinedValue");
        object.putNull("nullValue");
        object.put("booleanValue", false);
        object.put("innerObject", innerObject);
        object.put("innerArray", innerArray);

        System.out.println(object.containsKey("innerArray"));

        innerObject.put("oi", "m8");

        System.out.println(object.toJSON());
        System.out.println(object.size());

        System.out.println(object.get("numberValue"));
        System.out.println(object.get("stringValue"));

        object.remove("numberValue");
        System.out.println(object);

        System.out.println("Memory Usage: " + duktape.getHeapUsage());

        object.clear();
        System.out.println(object);

        System.out.println("Memory Usage: " + duktape.getHeapUsage());

        Object method = (Function.TwoArg.WithoutReturn<Integer, Long>) Main::lol;
        Class<?> clazz = method.getClass();
        Method invokeMethod = clazz.getMethods()[0];

        duktape.registerMethod("testMethod", method, invokeMethod, invokeMethod.getParameterCount());
        duktape.put("testValue", "I am a test value");
        duktape.execute("testMethod();");
    }

    public static void lol(int i, long j) {
        System.out.println("hello world!" + i);
    }

}
