#include <stdio.h>

#include "c_cache.h"
#include "c_storage.h"
#include "c_shared_allocator.h"

#include <string.h>
#include <pthread.h>

extern char *shared_name;
extern c_shared_header *shared_header;

int main(int argc, char const *argv[])
{
	char *error;
	unsigned int ks = 512*1024*1024;
	unsigned int vs = 1024*1024*1024;

	shared_name = "/tmp/shartest.tmp1";
	c_storage_startup(ks, vs, &error);
	printf("%s\n", error);
	printf("%d %lu %lu %lu\n", shared_header->segment_num, shared_header->k_offset, shared_header->v_offset, shared_header->k_size);
	return 0;
}