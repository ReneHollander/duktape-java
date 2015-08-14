package at.renehollander.duktape;

import at.renehollander.duktape.values.*;

public class Main {

    private Duktape duktape;

    public Main() throws Exception {
        System.out.println("Duktape Version " + Duktape.getVersion());

        this.duktape = new Duktape();

        DukBuffer dukBuffer = new DukBuffer(duktape, 1024);
        System.out.println(dukBuffer.getRef());
        System.out.println(dukBuffer.getByteBuffer());
        dukBuffer.getByteBuffer().put((byte) 18);
        System.out.println(dukBuffer.getByteBuffer().get(0));

        DukObject global = duktape.getGlobal();

        global.put("buffer", dukBuffer);
        System.out.println(global.get("buffer").asBuffer().getByteBuffer());
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
