#include <stdlib.h>
#include <duktape.h>
#include "memoryinfo.h"
#include "duktape_user_data.h"

void *counting_alloc_function(void *udata, duk_size_t size) {
    DuktapeUserData *userData = (DuktapeUserData *) udata;
    char *res = (char *) malloc(sizeof(size_t) + size);
    if (res != NULL) {
        *(size_t *) res = size;
        res = res + sizeof(size_t);
        userData->memoryInfo.currentHeapSize += size;
    }
    return res;
}

void *counting_realloc_function(void *udata, void *intpr, duk_size_t newsize) {
    char *ptr = (char *) intpr;
    if (ptr != NULL) {
        DuktapeUserData *userData = (DuktapeUserData *) udata;
        size_t oldSize = *(size_t *) (ptr - sizeof(size_t));
        userData->memoryInfo.currentHeapSize -= oldSize;
        char *res = (char *) realloc(ptr - sizeof(size_t), sizeof(size_t) + newsize);
        if (res != NULL) {
            *(size_t *) res = newsize;
            res = res + sizeof(size_t);
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
        DuktapeUserData *userData = (DuktapeUserData *) udata;
        size_t size = *(size_t *) (ptr - sizeof(size_t));
        userData->memoryInfo.currentHeapSize -= size;
        free(ptr - sizeof(size_t));
    }
}