package at.renehollander.duktape.values;

import at.renehollander.duktape.Destroyable;
import at.renehollander.duktape.Duktape;
import at.renehollander.duktape.Function;

import java.lang.reflect.Method;

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
        this.method = function.getClass().getMethods()[0];
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
            this.dukFunction = new DukFunction(this.getDuktape(), _createAndReference(this.getDuktape().getContextPointer(), this.getMethod(), this.getMethod().getParameterCount(), this.getObject()));
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

    private static native int _createAndReference(long contextPointer, Method method, int paramCount, Object object);

}
