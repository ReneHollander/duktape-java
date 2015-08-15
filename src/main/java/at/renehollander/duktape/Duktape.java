package at.renehollander.duktape;

import at.renehollander.duktape.annotation.ExposeToJavascript;
import at.renehollander.duktape.error.FatalErrorHandler;
import at.renehollander.duktape.values.DukFunction;
import at.renehollander.duktape.values.DukJavaFunction;
import at.renehollander.duktape.values.DukObject;
import at.renehollander.duktape.values.DukValue;

import java.io.File;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

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

    public DukValue execute(String script) {
        return _execute(this.getContextPointer(), script);
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

    public DukFunction toObjectPrototype(Class<?> clazz) {
        Constructor javascriptConstructor = null;
        List<Field> javascriptFields = new ArrayList<>();
        List<Method> javascriptMethods = new ArrayList<>();

        // check constructors
        for (Constructor<?> constructor : clazz.getConstructors()) {
            ExposeToJavascript etj = constructor.getAnnotation(ExposeToJavascript.class);
            if (etj != null) {
                if (javascriptConstructor != null) {
                    throw new IllegalArgumentException("You can only have one constructor with the ExposeToJavascript annotation");
                }
                javascriptConstructor = constructor;
            }
        }
        if (javascriptConstructor == null) {
            throw new IllegalArgumentException("You need to specify at least one constructor in the given class with the ExposeToJavascript annotation");
        }

        // check fields
        for (Field field : clazz.getFields()) {
            ExposeToJavascript etj = field.getAnnotation(ExposeToJavascript.class);
            if (etj != null) {
                if (!field.getType().equals(DukValue.class)) {
                    throw new IllegalArgumentException("Field " + field + " needs the type DukValue to get exported to javascript");
                }
                javascriptFields.add(field);
            }
        }

        // check methods
        for (Method method : clazz.getMethods()) {
            ExposeToJavascript etj = method.getAnnotation(ExposeToJavascript.class);
            if (etj != null) {
                javascriptMethods.add(DukJavaFunction.validateMethod(method));
            }
        }


        return null;
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

    private static native DukValue _execute(long contextPointer, String script);

    /* ==================================================================== */
    /* ========================= END native calls ========================= */
    /* ==================================================================== */

}
