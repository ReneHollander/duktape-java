#include "native-helper.h"
#include "duktape.h"
#include "helper.h"
#include "refs.h"

JNIEXPORT void JNICALL Java_at_renehollander_duktape_NativeHelper_unref(JNIEnv *env, jclass cls, jobject duktape, jint ref) {
    duk_context *ctx = getContextFromObject(env, duktape);
    duj_unref(ctx, ref);
}