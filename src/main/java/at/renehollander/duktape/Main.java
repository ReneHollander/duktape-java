package at.renehollander.duktape;

import at.renehollander.duktape.values.*;

import java.nio.ByteBuffer;

public class Main {

    private Duktape duktape;

    public Main() throws Exception {
        System.out.println("Duktape Version " + Duktape.getVersion());
        this.duktape = new Duktape();
        DukObject global = duktape.getGlobal();

        DukBuffer dukBuffer = DukBuffer.allocate(duktape, 16);
        ByteBuffer byteBuffer = dukBuffer.getByteBuffer();
        byteBuffer.put((byte) 1);
        global.put("buffer", dukBuffer);
        DukBuffer fromGlobal = global.get("buffer").as();
        System.out.println(fromGlobal.getByteBuffer().get(0));
        duktape.destroy();

    }

    public DukValue lol(DukValue v1, DukValue v2) {
        System.out.println("v1=" + v1 + ", v2=" + v2);
        if (v2.isFunction()) {
            DukFunction function = v2.asFunction();
            System.out.println("function invoke: " + function.invoke(new DukString(duktape, "Hello from java through javascript and back to java :D"), new DukNumber(duktape, 2)));
        }
        return new DukNumber(duktape, 5);
    }

    public static void main(String[] args) throws Exception {
        new Main();
    }

}
