
#ifndef C_SHARED_ALLOCATOR_H
#define C_SHARED_ALLOCATOR_H

#define USE_MMAP 1

#define C_CACHE_ALIGNMENT 			8
#define C_CACHE_ALIGNMENT_MARK		~(C_CACHE_ALIGNMENT - 1)

#define C_CACHE_FILE_MODEL			0660

#define C_CACHE_ALIGNED_SIZE(x)		(((x) + C_CACHE_ALIGNMENT - 1) & C_CACHE_ALIGNMENT_MARK)

int c_cache_allocator_startup();
void c_cache_allocator_shutdown();
void *c_cache_allocator_raw_alloc();
int c_cache_allocator_free(void *p);

#endif /* C_SHARED_ALLOCATOR_H */