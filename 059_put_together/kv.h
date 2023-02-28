#ifndef __KV_H__
#define __KV_H__

struct _kvpair_t {
  // An individual key value pair (2 strings, one for key , one for value)
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  // Array of pointers to key-value pairs, and the length of it
  kvpair_t ** pair_array;
  int num_pairs;
};
typedef struct _kvarray_t kvarray_t;

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
