#ifndef __COUNTS_H__
#define __COUNTS_H__
#include <stdio.h>

struct _one_count_t {
  //string and corresponding count
  char * string;
  int string_counts;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //array of pointers to each count
  one_count_t ** array_counts;
  int how_many;
  int unknowns;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
