
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

static int create_segments(const char *shared_name, c_shared_header **shared_header, unsigned long k_size, unsigned long v_size, unsigned int shared_segment_num, char **error_in) {
	unsigned long alloc_size, header_size, segment_size;
	int fd;
	void *p;

	k_size = C_CACHE_ALIGNED_SIZE(k_size);
	v_size = C_CACHE_ALIGNED_SIZE(v_size);
	header_size = (unsigned long)sizeof(c_shared_header);

	segment_size = v_size / shared_segment_num;
	++shared_segment_num;

	alloc_size = header_size + k_size + v_size;

	fd = open(shared_name, O_CREAT | O_EXCL | O_RDWR, C_CACHE_FILE_MODEL);

	if(fd == -1 && errno == EEXIST) {
		goto exist;
	} else if(fd == -1) {
		*error_in = "open";
		goto error;
	} else {
		goto create;
	}

create:
	p = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == (void*)-1) {
		*error_in = "mmap";
		goto error;
	}	

	if(ftruncate(fd, alloc_size) == -1) {
		*error_in = "ftruncate";
	}

	
	// unlink(shared_name);

exist:


error:

}

static void detach_segment(c_shared_segment *segment) {

}


#endif /* USE_MMAP */

