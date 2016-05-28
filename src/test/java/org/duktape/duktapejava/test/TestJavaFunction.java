package org.duktape.duktapejava.test;

import org.duktape.duktapejava.Duktape;
import org.duktape.duktapejava.duk_context;
import org.junit.Test;

import static org.duktape.duktapejava.Duktape.*;
import static org.junit.Assert.assertEquals;

public class TestJavaFunction {

    @Test
    public void testCallFromJavascriptToJava() {
        duk_context ctx = duk_create_context();

        final boolean[] itWorked = {false};

        duk_push_global_object(ctx);
        duk_push_java_function(ctx, new Duktape.Function() {
            @Override
            public int call(duk_context ctx) {
                itWorked[0] = true;
                return 0;
            }
        }, 0);
        duk_put_prop_string(ctx, -2, "javaFunction");
        duk_pop(ctx);

        duk_eval_string(ctx, "javaFunction();");

        assertEquals(true, itWorked[0]);

        duk_destroy_heap(ctx);
    }


}
