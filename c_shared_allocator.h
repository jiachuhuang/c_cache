
#ifndef C_SHARED_ALLOCATOR_H
#define C_SHARED_ALLOCATOR_H

#define USE_MMAP 1

#define C_ALLOC_ALIGNMENT 					8
#define C_ALLOC_ALIGNMENT_MARK				~(C_ALLOC_ALIGNMENT - 1)

#define C_ALLOC_FILE_MODEL					(S_IRUSR | S_IWUSR | S_IRGPR | S_IWGPR)
#define C_ALLOC_FILE_OPEN_CREAT_FLAG		(O_CREAT | O_EXCL | O_RDWR)
#define C_ALLOC_FILE_OPEN_FLAG				(O_RDWR)

#ifdef USE_MMAP
	#define MMAP_FAIL						((void*)-1)	
#else 
	#error(no builtin shared memory supported)	
#endif /* USE_MMAP */				

#define C_ALLOC_ALIGNED_SIZE(x)				(((x) + C_ALLOC_ALIGNMENT - 1) & C_ALLOC_ALIGNMENT_MARK)

int c_cache_allocator_startup();
void c_cache_allocator_shutdown();
void *c_cache_allocator_raw_alloc();
/* int c_cache_allocator_free(void *p); */

#endif /* C_SHARED_ALLOCATOR_H */