package test.at.renehollander.duktape;

import at.renehollander.duktape.Duktape;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class DuktapeTest {

    @Test
    public void createAndDestroyDuktape() {
        Duktape duktape = new Duktape();
        assertEquals(true, duktape.getContextPointer() != 0);
        duktape.destroy();
    }

    @Test
    public void testGetHeapUsage() {
        Duktape duktape = new Duktape();
        assertEquals(true, duktape.getHeapUsage() > 0);
        duktape.destroy();
    }


}
