#pragma once

struct MemoryInfo {
    size_t currentHeapSize;
};
typedef struct MemoryInfo MemoryInfo;

extern void *counting_alloc_function(void *udata, duk_size_t size);

extern void *counting_realloc_function(void *udata, void *ptr, duk_size_t newsize);

extern void counting_free_function(void *udata, void *ptr);

//void duk_default_fatal_handler(duk_context *ctx, duk_errcode_t code, const char *msg);