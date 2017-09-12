#include "c_cache.h"
#include "c_storage.h"
#include "c_shared_allocator.h"

#include <pthead.h>

#ifdef USE_MMAP
	#include "c_shared_mmap.c"
#else 
	#error(no builtin shared memory supported)	
#endif

int c_cache_allocator_startup(void **p, c_shared_header **shared_header, c_shared_segment **shared_segments, const char *shared_name, unsigned long k_size, unsigned long v_size, char **error_in) {
	int ret;

	ret = create_shmmap(p, shared_header, shared_segments, shared_name, k_size, v_size, error_in);

	if(ret == C_CACHE_FAIL) {
		return C_CACHE_FAIL;
	}

	return C_CACHE_OK;
}