package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.Function;

import java.lang.reflect.Method;
import java.util.Arrays;

public class DukJavaFunction implements Destroyable {

    private Duktape duktape;
    private Method method;
    private Object object;

    private DukFunction dukFunction;

    public DukJavaFunction(Duktape duktape, Method method, Object object) {
        this.duktape = duktape;
        this.method = method;
        this.object = object;
    }

    public DukJavaFunction(Duktape duktape, Function function) {
        this.duktape = duktape;
        this.method = validateMethod(function.getClass().getMethods()[0]);
        this.object = function;
    }

    public Duktape getDuktape() {
        return duktape;
    }

    public Object getObject() {
        return object;
    }

    public Method getMethod() {
        return method;
    }

    public DukFunction getDukFunction() {
        if (dukFunction == null) {
            this.dukFunction = new DukFunction(this.getDuktape(), _createAndReference(this.getDuktape().getContextPointer(), this.getMethod(), this.getMethod().getParameterCount(), this.getObject(), this.getMethod().getReturnType().equals(Void.TYPE)));
        }
        return this.dukFunction;
    }

    @Override
    public void destroy() throws Throwable {
        if (dukFunction != null) {
            this.dukFunction.destroy();
        }
    }

    @Override
    public boolean equals(Object o) {
        // TODO implement
        throw new UnsupportedOperationException("not yet implemented");
    }

    @Override
    public int hashCode() {
        // TODO implement
        throw new UnsupportedOperationException("not yet implemented");
    }

    private static native int _createAndReference(long contextPointer, Method method, int paramCount, Object object, boolean voidFunction);

    public static Method validateMethod(Method method) {
        if (!method.getReturnType().equals(Void.TYPE) && !method.getReturnType().equals(DukValue.class)) {
            throw new IllegalArgumentException("Method " + method + " must have either a void or DukValue return type");
        }
        Arrays.stream(method.getParameterTypes()).forEach((clazz) -> {
            if (!clazz.equals(DukValue.class)) {
                throw new IllegalArgumentException("Method " + method + " must only have DukValue as parameter types");
            }
        });
        return method;
    }

}
