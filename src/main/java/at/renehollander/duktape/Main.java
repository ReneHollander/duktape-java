package at.renehollander.duktape;

import at.renehollander.duktape.values.*;

import java.lang.reflect.Method;

public class Main {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();

        DukArray innerArray = new DukArray(duktape);

        DukObject innerObject = new DukObject(duktape);
        innerObject.put("heyo", new DukString(duktape, "captain jack"));

        DukObject object = new DukObject(duktape);
        object.put("numberValue", new DukNumber(duktape, 10));
        object.put("stringValue", new DukString(duktape, "lol"));
        object.put("undefinedValue", new DukUndefined(duktape));
        object.put("nullValue", new DukNull(duktape));
        object.put("booleanValue", new DukBoolean(duktape, false));
        object.put("innerObject", innerObject);
        object.put("innerArray", innerArray);
        System.out.println(object.toJSON());

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
