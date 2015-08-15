package at.renehollander.duktape;

import at.renehollander.duktape.annotation.ExposeToJavascript;
import at.renehollander.duktape.values.DukValue;

public class TestObject {

    @ExposeToJavascript
    public static DukValue staticValue;

    @ExposeToJavascript
    public DukValue value;

    @ExposeToJavascript
    public TestObject() {

    }

    @ExposeToJavascript
    public void doStuff(DukValue value) {
        System.out.println("doStuff: " + value);
    }

    @ExposeToJavascript
    public static void doStuffStatically() {
    }

}
