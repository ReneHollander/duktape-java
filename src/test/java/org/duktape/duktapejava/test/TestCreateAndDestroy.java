package org.duktape.duktapejava.test;

import org.duktape.duktapejava.duk_context;
import org.junit.Test;

import static org.duktape.duktapejava.Duktape.duk_create_context;
import static org.duktape.duktapejava.Duktape.duk_destroy_heap;

public class TestCreateAndDestroy {

    @Test
    public void createAndDestroy() {
        duk_context ctx = duk_create_context();
        duk_destroy_heap(ctx);
    }

    @Test
    public void destroyNull() {
        duk_destroy_heap(null);
    }

}
