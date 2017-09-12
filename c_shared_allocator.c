#include "c_cache.h"
#include "c_storage.h"
#include "c_shared_allocator.h"

#include <pthead.h>

#ifdef USE_MMAP
	#include "c_shared_mmap.c"
#else 
	#error(no builtin shared memory supported)	
#endif

int c_cache_allocator_startup(void **p, c_shared_header **shared_header, const char *shared_name, unsigned long k_size, unsigned long v_size, char **error_in) {
	int ret = 0, try = 0;
	int create = 0;
	pthread_rwlockattr_t rwattr;


	ret = create_segments(p, shared_name, &k_size, &v_size, &create, error_in);

	if(ret == C_CACHE_FAIL) {
		goto error;
	}

	if(create == 1) {
		goto new;
	} else {
		goto exist;
	}

new:	


exist:

error:
	return C_CACHE_FAIL;
}