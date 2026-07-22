#include <stdlib.h>

#ifndef N
#define N 1
#endif

void* __real_malloc(size_t size);
void* __real_calloc(size_t n, size_t size);

static unsigned alloc_cnt = 0;

void* __wrap_malloc(size_t size) {
  ++alloc_cnt;
  return alloc_cnt >= N ? NULL : __real_malloc(size);
}

void* __wrap_calloc(size_t n, size_t size) {
  ++alloc_cnt;
  return alloc_cnt >= N ? NULL : __real_calloc(n, size);
}
