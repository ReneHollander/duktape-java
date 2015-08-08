package at.renehollander.duktape;

import java.io.File;
import java.lang.reflect.Method;

public class Duktape {

    static {
        File libraryFile = new File("lib/libduktape-java.so");
        System.load(libraryFile.getAbsolutePath());
    }

    private long contextPtr;

    public Duktape() {
        createContext();
    }

    public void destroy() {
        this.destroyContext();
    }

    public long getContextPtr() {
        return contextPtr;
    }

    private native void createContext();

    private native void destroyContext();

    public native void put(String name, String value);

    public native void registerMethod(String name, Object callerObject, Method method, int paramCount);

    public native void execute(String script);

    public native long getHeapUsage();

    public native void gc();

}
