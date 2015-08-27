#pragma once

#include "jni.h"

struct ClassCache {
    struct {
        struct {
            jclass String;
        } lang;
    } java;

    struct {
        struct {
            struct {
                jclass Duktape;
                struct {
                    struct {
                        jclass DukReferencedValue;
                        jclass AbstractDukReferencedValue;
                        jclass DukError;
                        jclass DukBuffer;
                        jclass DukArray;
                        jclass DukFunction;
                        jclass DukObject;
                    } object;
                    struct {
                        jclass DukNull;
                        jclass DukNumber;
                        jclass DukString;
                        jclass DukUndefined;
                        jclass DukBoolean;
                    } primitive;
                } value;
            } duktape;
        } renehollander;
    } at;
};

struct MethodIDCache {
    struct {
        struct {
            struct {
                struct {
                    jmethodID fatalErrorHandler;
                } Duktape;
                struct {
                    struct {
                        struct {
                            jmethodID init;
                        } DukError;
                        struct {
                            jmethodID init;
                        } DukBuffer;
                        struct {
                            jmethodID init;
                        } DukArray;
                        struct {
                            jmethodID init;
                        } DukFunction;
                        struct {
                            jmethodID init;
                        } DukObject;

                    } object;
                    struct {
                        struct {
                            jmethodID init;
                        } DukNull;
                        struct {
                            jmethodID init;
                        } DukNumber;
                        struct {
                            jmethodID init;
                        } DukString;
                        struct {
                            jmethodID init;
                        } DukUndefined;
                        struct {
                            jmethodID init;
                        } DukBoolean;
                    } primitive;
                } value;
            } duktape;
        } renehollander;
    } at;
};

struct FieldIDCache {
    struct {
        struct {
            struct {
                struct {
                    struct {
                        struct {
                            jfieldID reference;
                        } DukArray;
                        struct {
                            jfieldID reference;
                        } DukObject;
                        struct {
                            jfieldID reference;
                        } AbstractDukReferencedValue;
                    } object;
                    struct {
                        struct {
                            jfieldID value;
                        } DukNumber;
                        struct {
                            jfieldID value;
                        } DukString;
                        struct {
                            jfieldID value;
                        } DukBoolean;
                    } primitive;
                } value;
            } duktape;
        } renehollander;
    } at;
};

typedef struct ClassCache ClassCache;
typedef struct MethodIDCache MethodIDCache;
typedef struct FieldIDCache FieldIDCache;

extern ClassCache classCache;
extern MethodIDCache methodIdCache;
extern FieldIDCache fieldIdCache;

void populateCache();