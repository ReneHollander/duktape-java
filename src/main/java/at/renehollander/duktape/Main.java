package at.renehollander.duktape;

import at.renehollander.duktape.values.DukArray;
import at.renehollander.duktape.values.DukObject;
import at.renehollander.duktape.values.DukValue;

public class Main {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();

        DukArray arr = new DukArray(duktape);

        DukObject object = new DukObject(duktape);
        object.put("key", "value");

        arr.add(object);

        for (int i = 0; i < 10; i++) {
            arr.add("Test String " + i);
        }

        for (DukValue value : arr) {
            System.out.println(value);
        }

        arr.destroy();

        duktape.destroy();
    }

}
