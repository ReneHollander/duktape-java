#include "duk-referenced-value.h"
#include "duktape.h"
#include "helper.h"
#include "refs.h"


JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukReferencedValue_unref(JNIEnv *env, jobject dukReferencedValue) {
    duk_context *ctx = getContextFromDukValue(env, dukReferencedValue);
    int ref = getRefFromDukReferencedValue(env, dukReferencedValue);
    duj_unref(ctx, ref);
}