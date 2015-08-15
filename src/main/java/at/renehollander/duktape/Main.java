package at.renehollander.duktape;

import at.renehollander.duktape.values.DukFunction;
import at.renehollander.duktape.values.DukJavaFunction;
import at.renehollander.duktape.values.DukObject;
import at.renehollander.duktape.values.DukValue;

public class Main {

    private Duktape duktape;

    public Main() throws Exception {
        System.out.println("Duktape Version " + Duktape.getVersion());

        this.duktape = new Duktape();

        System.out.println(duktape.toObjectPrototype(TestObject.class));

        DukObject global = duktape.getGlobal();
        DukJavaFunction testObject = new DukJavaFunction(this.duktape, (Function.TwoArg.WithoutReturn) this::lol);
        DukFunction testObjectConstructor = testObject.getDukFunction();
        DukObject testObjectConstructorPrototype = new DukObject(duktape);
        testObjectConstructorPrototype.put("lol", 1234);
        testObjectConstructor.put("prototype", testObjectConstructorPrototype);
        global.put("TestObject", testObjectConstructor);
        global.put("key", "value");
        System.out.println(duktape.getGlobal());
        duktape.execute("var to = new TestObject(key, 5); print(to.lol)");

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
    }

    public static void main(String[] args) throws Exception {
        new Main();
    }

}
