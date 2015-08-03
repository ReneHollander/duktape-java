package at.renehollander.duktape;

import java.lang.reflect.Method;

public class Main {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();

        Object method = (Function.NoArg.WithoutReturn) Main::lol;
        Class<?> clazz = method.getClass();
        Method invokeMethod = clazz.getMethods()[0];

        duktape.registerMethod("testMethod", method, invokeMethod);
        duktape.put("testValue", "I am a test value");
        duktape.execute("testMethod();");
    }

    public static void lol() {
        System.out.println("hello world!");
    }

}
