
#ifndef C_SHARED_ALLOCATOR_H
#define C_SHARED_ALLOCATOR_H

int c_cache_allocator_startup();
void c_cache_allocator_shutdown();
void *c_cache_allocator_raw_alloc();
int c_cache_allocator_free(void *p);

#endif /* C_SHARED_ALLOCATOR_H */