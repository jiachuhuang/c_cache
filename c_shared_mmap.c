
#include "c_cache.h"
#include "c_storage.h"
#include "c_shared_allocator.h"

#ifdef USE_MMAP

#include <pthead.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>  
#include <fcntl.h>
#include <sys/stat.h>

static int create_segments(void **p, const char *shared_name, unsigned long *k_size, unsigned long *v_size, unsigned int *create, char **error_in) {
	unsigned long alloc_size, header_size;
	int fd;
	int try = 0;

	// pthread_rwlockattr_t rwattr;

	*k_size = C_ALLOC_ALIGNED_SIZE(*k_size);
	*v_size = C_ALLOC_ALIGNED_SIZE(*v_size);
	header_size = (unsigned long)sizeof(c_shared_header);

	alloc_size = header_size + *k_size + *v_size;

again:
	if(try > 3) {
		*error_in = "timeout";
		goto error;
	}

	fd = open(shared_name, C_ALLOC_FILE_OPEN_CREAT_FLAG, C_ALLOC_FILE_MODEL);

	if(fd == -1 && errno == EEXIST) {
		goto exist;
	} else if(fd == -1) {
		*error_in = "open";
		goto error;
	} else {
		*create = 1;
		goto new;
	}

new:
	if(ftruncate(fd, alloc_size) == -1) {
		*error_in = "ftruncate";
		goto error;
	}

	*p = (void*)mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(*p == MMAP_FAIL) {
		*error_in = "mmap";
		goto error;
	}	

	close(fd);

	// init shared header
	// *shared_header = (c_shared_header *)*p;
	
	// *shared_header->k_size = k_size;
	// *shared_header->v_size = v_size;

	// *shared_header->segment_num = shared_segment_num;
	// *shared_header->segment_size = segment_size;

	// *shared_header->k_offset = (unsigned long)sizeof(c_shared_header);
	// *shared_header->v_offset = *shared_header->k_offset + *shared_header->k_size;

	// if(pthread_rwlockattr_init(&rwattr) != 0) {
	// 	*error_in = "pthread_rwlockattr_init";
	// 	goto error;
	// }
	// if(pthread_rwlockattr_setpshared(&rwattr, PTHREAD_PROCESS_SHARED) != 0) {
	// 	*error_in = "pthread_rwlockattr_setpshared";
	// 	pthread_rwlockattr_destroy(&rwattr);
	// 	goto error;
	// }

	return C_CACHE_OK;

exist:
	fd = open(shared_name, C_ALLOC_FILE_OPEN_FLAG, C_ALLOC_FILE_MODEL);
	if(fd == -1) {
		if(errno == ENOENT) {
			++try;
			goto again;
		}
	}

	*p = (void*)mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(*p == MMAP_FAIL) {
		*error_in = "mmap";
		goto error;
	}	

	close(fd);	

	*create = 0;

	return C_CACHE_OK;
	
error:
	if(fd > 0) {
		close(fd);
	}

	if(*create) {
		unlink(shared_name);
	}

	if(*p != MMAP_FAIL) {
		munmap(*p, alloc_size);
	}

	return C_CACHE_FAIL;
}

static void detach_segment(c_shared_segment *segment) {

}


#endif /* USE_MMAP */

