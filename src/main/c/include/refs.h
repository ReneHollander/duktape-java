#pragma once

#include "duktape.h"

/*
Borrowed from https://github.com/creationix/dukluv/blob/master/src/refs.h

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

// Create a global array refs in the heap stash.
void duj_ref_setup(duk_context *ctx);

// like luaL_ref, but assumes storage in "refs" property of heap stash
int duj_ref(duk_context *ctx);

void duj_push_ref(duk_context *ctx, int ref);

void duj_unref(duk_context *ctx, int ref);

int duj_get_ref_count(duk_context *ctx);

void duj_ref(duk_context *ctx, const char *name);

void duj_push_ref(duk_context *ctx, const char *name);

void duj_unref(duk_context *ctx, const char *name);

const char *duj_get_heap_stash_json(duk_context *ctx, const char *name);