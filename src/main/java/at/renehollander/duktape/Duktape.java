package at.renehollander.duktape;

import at.renehollander.duktape.error.FatalErrorHandler;
import at.renehollander.duktape.values.DukObject;

import java.io.File;

public class Duktape {

    static {
        File libraryFile = new File("lib/libduktape-java.so");
        System.load(libraryFile.getAbsolutePath());
    }

    private FatalErrorHandler fatalErrorHandler;

    private long contextPointer;

    public Duktape() {
        this.contextPointer = _createContext(this);
    }

    public void destroy() {
        _destroyContext(this.getContextPointer());
    }

    public long getContextPointer() {
        return contextPointer;
    }

    public DukObject getGlobal() {
        return DukObject.getGlobal(this);
    }

    public void execute(String script) {
        _execute(this.getContextPointer(), script);
    }

    public long getHeapUsage() {
        return _getHeapUsage(this.getContextPointer());
    }

    public void gc() {
        _gc(this.getContextPointer());
    }

    private void fatalErrorHandler(int code, String msg) {
        if (this.fatalErrorHandler != null) {
            this.fatalErrorHandler.fatalError(code, msg);
        }
    }

    public int getRefCount() {
        return _getRefCount(this.getContextPointer());
    }

    public void setFatalErrorHandler(FatalErrorHandler handler) {
        this.fatalErrorHandler = handler;
    }

    public static String getVersion() {
        return _getVersion();
    }

    /* ==================================================================== */
    /* ======================== START native calls ======================== */
    /* ==================================================================== */

    private static native String _getVersion();

    private static native long _createContext(Duktape duktape);

    private static native void _destroyContext(long contextPointer);

    private static native int _getRefCount(long contextPointer);

    private static native void _gc(long contextPointer);

    private static native long _getHeapUsage(long contextPointer);

    private static native void _execute(long contextPointer, String script);

    /* ==================================================================== */
    /* ========================= END native calls ========================= */
    /* ==================================================================== */

}
