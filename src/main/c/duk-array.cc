#include "duk-array.h"
#include "duktape.h"
#include "helper.h"
#include "cache.h"
#include "refs.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukArray_createEmptyArray(JNIEnv *env, jclass cls, jobject duktape) {
    duk_context *ctx = getContextFromObject(env, duktape);
    duk_push_array(ctx);
    return duj_ref(ctx);
}