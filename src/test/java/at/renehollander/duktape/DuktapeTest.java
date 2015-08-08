package at.renehollander.duktape;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class DuktapeTest {

    @Test
    public void createAndDestroyDuktape() {
        Duktape duktape = new Duktape();
        assertEquals(true, duktape.getContextPtr() != 0);
        duktape.destroy();
    }

    @Test
    public void testGetHeapUsage() {
        Duktape duktape = new Duktape();
        assertEquals(true, duktape.getHeapUsage() > 0);
        duktape.destroy();
    }


}
