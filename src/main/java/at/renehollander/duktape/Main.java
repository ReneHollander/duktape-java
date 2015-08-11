package at.renehollander.duktape;

import at.renehollander.duktape.values.DukObject;
import at.renehollander.duktape.values.DukString;
import at.renehollander.duktape.values.DukValue;

import java.util.Map;

public class Main {

    public static void main(String[] args) {

        System.out.println("Duktape Version " + Duktape.getVersion());

        Duktape duktape = new Duktape();

        DukObject dukObject = new DukObject(duktape);
        DukObject inner = new DukObject(duktape);
        dukObject.put("key", "value");
        dukObject.put("inner", inner);

        for (Map.Entry<String, DukValue> entry : dukObject.entrySet()) {
            System.out.println(entry);
            if (entry.getValue().isReferenceValue()) entry.getValue().asReferencedValue().destroy();
        }

        System.out.println(dukObject.containsValue(new DukString(duktape, "value")));

        System.out.println(duktape.getRefCount());

        duktape.destroy();
    }

}
