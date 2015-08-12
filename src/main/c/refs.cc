#include <duktape_user_data.h>
#include <helper.h>
#include "refs.h"

/*
Borrowed from https://github.com/creationix/dukluv/blob/master/src/refs.c

The MIT License (MIT)

Copyright (c) 2014 Tim Caswell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define DUJ_INDEXED_REFSTORE_NAME "indexed_refstore"
#define DUJ_NAMED_REFSTORE_NAME "named_refstore"

// Create a global array refs in the heap stash.
void duj_ref_setup(duk_context *ctx) {
    duk_push_heap_stash(ctx);

    // Create a new array with one `0` at index `0`.
    duk_push_array(ctx);
    duk_push_int(ctx, 0);
    duk_put_prop_index(ctx, -2, 0);
    // Store it as "refs" in the heap stash
    duk_put_prop_string(ctx, -2, DUJ_INDEXED_REFSTORE_NAME);

    duk_push_object(ctx);
    duk_put_prop_string(ctx, -2, DUJ_NAMED_REFSTORE_NAME);

    duk_pop(ctx);
}

int duj_get_ref_count(duk_context *ctx) {
    // Get the "refs" array in the heap stash
    duk_push_heap_stash(ctx);

    duk_get_prop_string(ctx, -1, DUJ_INDEXED_REFSTORE_NAME);

    int count = 0;

    duk_enum(ctx, -1, 0);
    while (duk_next(ctx, -1, DUK_ENUM_INCLUDE_NONENUMERABLE)) {
        if (duk_is_number(ctx, -1) == 0) {
            count++;
        }
        duk_pop_2(ctx);
    }

    duk_pop(ctx);
    duk_pop(ctx);
    duk_pop(ctx);

    return count;
}

const char *duj_get_heap_stash_json(duk_context *ctx, const char *name) {
    duk_push_heap_stash(ctx);
    const char *json = duk_json_encode(ctx, 0);
    duk_pop(ctx);
    return json;
}


// like luaL_ref, but assumes storage in "refs" property of heap stash
int duj_ref(duk_context *ctx) {

    if (duk_is_number(ctx, -1)) {
        return -1;
    }

    int ref;
    if (duk_is_undefined(ctx, -1)) {
        duk_pop(ctx);
        return 0;
    }
    // Get the "refs" array in the heap stash
    duk_push_heap_stash(ctx);
    duk_get_prop_string(ctx, -1, DUJ_INDEXED_REFSTORE_NAME);
    duk_remove(ctx, -2);

    // ref = refs[0]
    duk_get_prop_index(ctx, -1, 0);
    ref = duk_get_int(ctx, -1);
    duk_pop(ctx);

    // If there was a free slot, remove it from the list
    if (ref != 0) {
        // refs[0] = refs[ref]
        duk_get_prop_index(ctx, -1, (duk_uarridx_t) ref);
        duk_put_prop_index(ctx, -2, 0);
    }
        // Otherwise use the end of the list
    else {
        // ref = refs.length;
        ref = (int) duk_get_length(ctx, -1);
    }

    // swap the array and the user value in the stack
    duk_insert(ctx, -2);

    // refs[ref] = value
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) ref);

    // Remove the refs array from the stack.
    duk_pop(ctx);

    return ref;
}

void duj_push_ref(duk_context *ctx, int ref) {
    if (!ref) {
        duk_push_undefined(ctx);
        return;
    }
    // Get the "refs" array in the heap stash
    duk_push_heap_stash(ctx);
    duk_get_prop_string(ctx, -1, DUJ_INDEXED_REFSTORE_NAME);
    duk_remove(ctx, -2);

    duk_get_prop_index(ctx, -1, (duk_uarridx_t) ref);

    duk_remove(ctx, -2);
}

static void _duj_unref(duk_context *ctx, int ref) {

    if (!ref) return;

    // Get the "refs" array in the heap stash
    duk_push_heap_stash(ctx);
    duk_get_prop_string(ctx, -1, DUJ_INDEXED_REFSTORE_NAME);
    duk_remove(ctx, -2);

    // Insert a new link in the freelist

    // refs[ref] = refs[0]
    duk_get_prop_index(ctx, -1, 0);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) ref);
    // refs[0] = ref
    duk_push_int(ctx, ref);
    duk_put_prop_index(ctx, -2, 0);

    duk_pop(ctx);
}

void duj_unref(duk_context *ctx, int ref) {
    duj_check_marked_for_unref(ctx);
    _duj_unref(ctx, ref);
}

void duj_mark_for_unref(duk_context *ctx, int ref) {
    DuktapeUserData *userData = getDuktapeUserData(ctx);
    userData->unrefData.mark_for_unref_indexed->push_back(ref);
}

void duj_ref(duk_context *ctx, const char *name) {
    duk_push_heap_stash(ctx);
    duk_get_prop_string(ctx, -1, DUJ_NAMED_REFSTORE_NAME);
    duk_remove(ctx, -2);
    // swap the object and the user value in the stack
    duk_insert(ctx, -2);
    duk_put_prop_string(ctx, -2, name);
    duk_pop(ctx);
}

void duj_push_ref(duk_context *ctx, const char *name) {
    duk_push_heap_stash(ctx);
    duk_get_prop_string(ctx, -1, DUJ_NAMED_REFSTORE_NAME);
    duk_remove(ctx, -2);
    duk_get_prop_string(ctx, -1, name);
    duk_remove(ctx, -2);
}

static void _duj_unref(duk_context *ctx, const char *name) {
    duk_push_heap_stash(ctx);
    duk_get_prop_string(ctx, -1, DUJ_NAMED_REFSTORE_NAME);
    duk_del_prop_string(ctx, -1, name);
    duk_pop_2(ctx);
}

void duj_unref(duk_context *ctx, const char *name) {
    duj_check_marked_for_unref(ctx);
    _duj_unref(ctx, name);
}

void duj_mark_for_unref(duk_context *ctx, const char *name) {
    DuktapeUserData *userData = getDuktapeUserData(ctx);
    userData->unrefData.mark_for_unref_named->push_back(std::string(name));
}

void duj_check_marked_for_unref(duk_context *ctx) {
    DuktapeUserData *userData = getDuktapeUserData(ctx);

    for (unsigned long i = 0; i < userData->unrefData.mark_for_unref_indexed->size(); i++) {
        int ref = userData->unrefData.mark_for_unref_indexed->at(i);
        _duj_unref(ctx, ref);
    }
    userData->unrefData.mark_for_unref_indexed->clear();

    for (unsigned long i = 0; i < userData->unrefData.mark_for_unref_named->size(); i++) {
        std::string ref = userData->unrefData.mark_for_unref_named->at(i);
        _duj_unref(ctx, ref.c_str());
    }
    userData->unrefData.mark_for_unref_named->clear();
}