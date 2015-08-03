package at.renehollander.duktape;

import java.io.File;
import java.lang.reflect.Method;

public class Duktape {

    static {
        File libraryFile = new File("build/libduktape-java.so");
        System.load(libraryFile.getAbsolutePath());
    }

    private long contextPtr;

    public Duktape() {
        createContext();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        destroyContext();
    }

    private native void createContext();

    private native void destroyContext();

    public native void put(String name, String value);

    public native void registerMethod(String name, Object object, Method method);

    public native void execute(String script);

}
