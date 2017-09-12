#include <pthead.h>

#ifndef C_STORAGE_H
#define C_STORAGE_H

#define C_STORAGE_MAX_KEY_LEN (48)
#define C_STORAGE_MIN_SEGMENT_SIZE (8*1024*1024)
#define C_STORAGE_MAX_SEGMENT_SIZE (128*1024*1024)


typedef struct {
	pthread_rwlock_t rlock;
	pthread_rwlock_t wlock;
	unsigned long k_size;
	unsigned long v_size;
	unsigned int segment_num;
	unsigned int segment_size;
	/* unsigned int miss; */
	/* unsigned int fails; */
	/* unsigned long hits; */
	unsigned long k_offset;
	unsigned long v_offset;
} c_shared_header;

typedef struct {
	pthread_rwlock_t rlock;
	pthread_rwlock_t wlock;
	unsigned int pos;
	unsigned int size;
	unsigned long s_offset;
} c_shared_segment;

typedef struct {
	unsigned long offset;
	unsigned int segment_index;
	unsigned int len;
	unsigned long atime;
} c_kv_val;

typedef struct {
	unsigned long h;
	unsigned long crc;
	unsigned int ttl;
	unsigned int atime;
	unsigned int size;
	unsigned int len;
	/* unsigned int flag; */
	unsigned char key[C_STORAGE_MAX_KEY_LEN];
	c_kv_val val;
} c_kv_key;

int c_storage_startup(unsigned int k_size, unsigned int v_size, unsigned char **msg);
void c_storage_shutdown();
int c_storage_find(char *key, unsigned int len, void **data,/* unsigned int *flag,*/ unsigned long tv);
int c_storage_update(char* key, unsigned int len, void* data, unsigned int size, unsigned int ttl,/* unsigned int *flag,*/ unsigned int add, unsigned long tv);
int c_storage_delete(char* key, unsigned int len, unsigned long tv);
int c_storage_flush();
int c_storage_get_info();
int c_storage_exists(char* key, unsigned int len);

#endif /* C_STORAGE_H */
