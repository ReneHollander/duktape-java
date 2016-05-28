#include "duktape.h"

struct memory_info {
    duk_int64_t currentHeapSize;
};

struct userdata {
    struct memory_info memoryInfo;
};

void *counting_alloc_function(void *udata, duk_size_t size) {
    struct userdata *userData = (struct userdata *) udata;
    char *res = (char *) malloc(sizeof(duk_int64_t) + size);
    if (res != NULL) {
        *(duk_int64_t *) res = size;
        res = res + sizeof(duk_int64_t);
        userData->memoryInfo.currentHeapSize += size;
    }
    return res;
}

void *counting_realloc_function(void *udata, void *intpr, duk_size_t newsize) {
    char *ptr = (char *) intpr;
    if (ptr != NULL) {
        struct userdata *userData = (struct userdata *) udata;
        duk_int64_t oldSize = *(duk_int64_t *) (ptr - sizeof(duk_int64_t));
        userData->memoryInfo.currentHeapSize -= oldSize;
        char *res = (char *) realloc(ptr - sizeof(duk_int64_t), sizeof(duk_int64_t) + newsize);
        if (res != NULL) {
            *(duk_int64_t *) res = newsize;
            res = res + sizeof(duk_int64_t);
            userData->memoryInfo.currentHeapSize += newsize;
        }
        return res;
    } else {
        return counting_alloc_function(udata, newsize);
    }
}

void counting_free_function(void *udata, void *inptr) {
    char *ptr = (char *) inptr;
    if (ptr != NULL) {
        struct userdata *userData = (struct userdata *) udata;
        duk_int64_t size = *(duk_int64_t *) (ptr - sizeof(duk_int64_t));
        userData->memoryInfo.currentHeapSize -= size;
        free(ptr - sizeof(duk_int64_t));
    }
}

extern duk_context *duk_create_context_with_fatal_handler(duk_fatal_function fatal_handler) {
    struct userdata *userData = (struct userdata *) malloc(sizeof(struct userdata));
    userData->memoryInfo.currentHeapSize = 0;
    return duk_create_heap(counting_alloc_function, counting_realloc_function, counting_free_function, userData, fatal_handler);
}

extern duk_context *duk_create_context(void) {
    return duk_create_context_with_fatal_handler(NULL);
}

extern void *duk_get_userdata(duk_context *ctx) {
    duk_memory_functions functions;
    duk_get_memory_functions(ctx, &functions);
    return functions.udata;
}

extern duk_int64_t duk_get_memory_usage(duk_context *ctx) {
    struct userdata *userData = (struct userdata *) duk_get_userdata(ctx);
    return userData->memoryInfo.currentHeapSize;
}