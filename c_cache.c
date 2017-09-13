#include <stdio.h>

#include "c_cache.h"
#include "c_storage.h"
#include "c_shared_allocator.h"

#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

extern c_shared_header *shared_header;

int c_cache_get(char *key, unsigned int len, void **data, unsigned int *size) {
	time_t tv;
	tv = time((time_t *)NULL);

	return c_storage_find(key, len, data, size, tv);
}

int c_cache_set(char *key, unsigned int len, void *data, unsigned int size, unsigned int ttl) {
	time_t tv;
	tv = time((time_t *)NULL);

	if(ttl <= 0) {
		ttl = (unsigned int)tv + 2 * 60 * 60;
	} else {
		ttl += tv;
	}

	return c_storage_update(key, len, data, size, ttl, 0, tv);
}

void c_cache_flush() {
	c_storage_flush();
}

int c_cache_delete(char *key, unsigned int len) {
	return c_storage_delete(key, len);
}

int main(int argc, char const *argv[]) {
	char *error;
	unsigned int ks = 512*1024*1024;
	unsigned int vs = 1024*1024*1024;

	c_storage_startup("/tmp/shartest.tmp1", ks, vs, &error);
	printf("%s\n", error);
	
	char *key = "abd";
	void *data;
	unsigned int size;
	int ret;

	char resutl[4];

	// ret = c_cache_set(key, (unsigned int)strlen(key), (void*)"hjc", strlen("hjc"), 0);
	// printf("set: %d\n", ret);
	ret = c_cache_get(key, (unsigned int)strlen(key), &data, &size);

	if(ret) {
		memcpy(resutl, data, 3);
		resutl[3] = '\0';
		printf("get: %s\n", resutl);
		printf("%d\n", shared_header->segment_num);
	}
	c_storage_shutdown();
	return 0;
}



















