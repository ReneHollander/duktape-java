package test.at.renehollander.duktape;

import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.util.Function;
import at.renehollander.duktape.value.*;
import at.renehollander.duktape.value.object.DukArray;
import at.renehollander.duktape.value.object.DukJavaFunction;
import at.renehollander.duktape.value.object.DukObject;
import at.renehollander.duktape.value.primitive.*;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class DukObjectTest {

    @Test
    public void createAndDestroy() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        assertEquals(true, dukObject.getRef() > 0);
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDouble() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        dukObject.put("key", 1D);
        assertEquals(1D, dukObject.get("key").asNumber(), 0.0);
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetBoolean() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        dukObject.put("key", true);
        assertEquals(true, dukObject.get("key").asBoolean());
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetString() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        dukObject.put("key", "value");
        assertEquals("value", dukObject.get("key").asString());
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetUndefined() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        dukObject.putUndefined("key");
        assertEquals(true, dukObject.get("key").isUndefined());
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetNull() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        dukObject.putNull("key");
        assertEquals(true, dukObject.get("key").isNull());
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukArray() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        DukArray dukArray = new DukArray(duktape);
        dukArray.add(1D);
        dukObject.put("key", dukArray);
        assertEquals(1D, dukObject.get("key").asArray().get(0).asNumber(), 0.0);
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukFunction() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        DukJavaFunction dukJavaFunction = new DukJavaFunction(duktape, (Function.OneArg.WithReturn) (arg1) -> arg1);
        dukObject.put("key", dukJavaFunction.getDukFunction());
        assertEquals(true, dukObject.get("key").asFunction().invoke(new DukBoolean(duktape, true)).asBoolean());
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukObject() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);
        DukObject dukInner = new DukObject(duktape);
        dukInner.put("innerKey", "innerValue");
        dukObject.put("key", dukInner);
        assertEquals("innerValue", dukObject.get("key").asObject().get("innerKey").asString());
        dukInner.destroy();
        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukNumber() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", new DukNumber(duktape, 1));
        assertEquals(1D, dukObject.get("key").asNumber(), 0.0);

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukBoolean() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", new DukBoolean(duktape, true));
        assertEquals(true, dukObject.get("key").asBoolean());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukString() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", new DukString(duktape, "value"));
        assertEquals("value", dukObject.get("key").asString());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukUndefined() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", new DukUndefined(duktape));
        assertEquals(true, dukObject.get("key").isUndefined());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void putGetDukNull() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", new DukNull(duktape));
        assertEquals(true, dukObject.get("key").isNull());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void containsKey() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(true, dukObject.containsKey("key"));

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void doesNotContainsKey() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(false, dukObject.containsKey("thisisnotavalidkey"));

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void containsValue() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(true, dukObject.containsValue(new DukString(duktape, "value")));

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void doesNotContainValue() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(false, dukObject.containsValue(new DukString(duktape, "iamnotintheobject")));

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void invalidGet() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(true, dukObject.get(1D).isUndefined());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void removeKey() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        dukObject.remove("key");
        assertEquals(true, dukObject.get("key").isUndefined());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void checkRemoveOldValue() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        DukValue oldValue = dukObject.remove("key");
        assertEquals("value", oldValue.asString());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void invalidRemove() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(true, dukObject.remove("iamnotcorrect").isUndefined());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void toJSON() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals("{\"key\":\"value\"}", dukObject.toJSON());

        dukObject.destroy();
        duktape.destroy();
    }

    @Test
    public void size() {
        Duktape duktape = new Duktape();
        DukObject dukObject = new DukObject(duktape);

        dukObject.put("key", "value");
        assertEquals(1, dukObject.size());

        dukObject.destroy();
        duktape.destroy();
    }

}
