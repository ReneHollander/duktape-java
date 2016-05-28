package org.duktape.duktapejava;

import static org.duktape.duktapejava.Duktape.*;

public class Example {
    public static void main(String[] args) {
        duk_context ctx = duk_create_context();

        duk_push_global_object(ctx);
        duk_push_java_function(ctx, (context) -> {
            System.out.println("Hello from Java!");
            return 0;
        }, 0);
        duk_put_prop_string(ctx, -2, "javaFunction");
        duk_pop(ctx);

        duk_eval_string(ctx, "javaFunction();");

        duk_destroy_heap(ctx);
    }
}
