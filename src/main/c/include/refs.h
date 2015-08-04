#pragma once

#include "duktape.h"

// Create a global array refs in the heap stash.
void duj_ref_setup(duk_context *ctx);
// like luaL_ref, but assumes storage in "refs" property of heap stash
int duj_ref(duk_context *ctx);
void duj_push_ref(duk_context *ctx, int ref);
void duj_unref(duk_context *ctx, int ref);
