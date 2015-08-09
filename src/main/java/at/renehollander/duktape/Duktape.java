package at.renehollander.duktape;

import at.renehollander.duktape.error.FatalErrorHandler;

import java.io.File;
import java.lang.reflect.Method;

public class Duktape {

    static {
        File libraryFile = new File("lib/libduktape-java.so");
        System.load(libraryFile.getAbsolutePath());
    }

    private FatalErrorHandler fatalErrorHandler;

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

    private void fatalErrorHandler(int code, String msg) {
        if (this.fatalErrorHandler != null) {
            this.fatalErrorHandler.fatalError(code, msg);
        }
    }

    public native int getRefCount();

    public void setFatalErrorHandler(FatalErrorHandler handler) {
        this.fatalErrorHandler = handler;
    }

}
