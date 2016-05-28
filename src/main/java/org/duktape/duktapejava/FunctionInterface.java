package org.duktape.duktapejava;

@FunctionalInterface
public interface FunctionInterface {

    int call(duk_context ctx);

    default Duktape.Function asFunction() {
        return new Duktape.Function() {
            @Override
            public int call(duk_context ctx) {
                return FunctionInterface.this.call(ctx);
            }
        };
    }

}
