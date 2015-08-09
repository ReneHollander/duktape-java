#pragma once

#include "duktape.h"

struct MemoryInfo {
    size_t currentHeapSize;
};
typedef struct MemoryInfo MemoryInfo;

extern void *counting_alloc_function(void *udata, duk_size_t size);

extern void *counting_realloc_function(void *udata, void *ptr, duk_size_t newsize);

extern void counting_free_function(void *udata, void *ptr);
