#include "duktape.h"
#include "duktape-java.h"

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_execute (JNIEnv *env, jobject obj, jstring script) {
    const char *nativeString = (*env)->GetStringUTFChars(env, script, 0);
    duk_context *ctx = duk_create_heap_default();
    duk_eval_string(ctx, nativeString);
    duk_destroy_heap(ctx);
    (*env)->ReleaseStringUTFChars(env, script, nativeString);
}