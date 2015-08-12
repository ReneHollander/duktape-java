package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.lang.reflect.Method;

public class DukJavaFunction {

    private Duktape duktape;
    private Method method;
    private Object object;

    private DukFunction dukFunction;

    public DukJavaFunction(Duktape duktape, Method method, Object object) {
        this.duktape = duktape;
        this.method = method;
        this.object = object;
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

    private static native int _createAndReference(long contextPointer, Method method, int paramCount, Object object);
}
