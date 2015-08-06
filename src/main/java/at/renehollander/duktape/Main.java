package at.renehollander.duktape;

import at.renehollander.duktape.values.*;

import java.lang.reflect.Method;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();

        DukObject innerObject = new DukObject(duktape);
        innerObject.put("heyo", "captain jack");

        DukObject innerObject2 = new DukObject(duktape);
        innerObject2.put("innerObject2", "heyo");

        DukObject innerObject3 = new DukObject(duktape);
        innerObject3.put("innerObject3", "heyo");

        DukArray array = new DukArray(duktape);
        array.add(5);
        array.add(10);
        array.add(innerObject);
        array.add(innerObject2);
        array.add(innerObject3);
        System.out.println(array);
        System.out.println(array.size());

        System.out.println(array.get(4));


        System.out.println("Initial Memory Usage: " + duktape.getHeapUsage());
        DukArray innerArray = new DukArray(duktape);

        //DukObject innerObject = new DukObject(duktape);
        //innerObject.put("heyo", "captain jack");

        DukObject object = new DukObject(duktape);
        object.put("numberValue", 10);
        object.put("stringValue", "fag");
        object.putUndefined("undefinedValue");
        object.putNull("nullValue");
        object.put("booleanValue", false);
        object.put("innerObject", innerObject);
        object.put("innerArray", innerArray);


        System.out.println(object.containsKey("innerArray"));

        System.out.println("innerObject: " + object.get("innerObject").toString());

        innerObject.put("oi", "m8");

        System.out.println(object.toJSON());
        System.out.println(object.size());

        System.out.println("numberValue: " + object.get("numberValue"));
        System.out.println("stringValue: " + object.get("stringValue"));

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
