#include "kv.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * copyString(char * source, char * dest, int start, int end) {
  if (dest == NULL) {
    fprintf(stderr, "Cant allocate key OR value\n");
    return NULL;
  }
  char * p2 = strchr(source, start);
  char * stop = strchr(source, end);
  size_t count = 0;
  if (start == '=') {
    p2++;
  }
  while (p2 != stop) {
    dest = realloc(dest, sizeof(*p2) + count + 1);
    dest[count] = *p2;
    count++;
    p2++;
  }
  dest[count] = '\0';
  return dest;
}

kvarray_t * readLines(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  int i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    if (curr == NULL) {
      fprintf(stderr, "Cant read line\n");
      exit(EXIT_FAILURE);
    }
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  // Allocate memory for the keyValue struct
  kvarray_t * keyValues = malloc(sizeof(*keyValues));  //allocate memory for array of KVs
  if (keyValues == NULL) {
    fprintf(stderr, "Cant allocate kvaray\n");
    free(lines);
    exit(EXIT_FAILURE);
  }
  keyValues->num_pairs = i;
  // Allocate memory for array of key values
  keyValues->pair_array = malloc(keyValues->num_pairs * sizeof(*keyValues->pair_array));
  // Allocate memory for each key and each value pair AND each key and value
  if (keyValues->pair_array == NULL) {
    fprintf(stderr, "Cant allocate kvaray\n");
    freeKVs(keyValues);
    free(lines);
    exit(EXIT_FAILURE);
  }
  for (int j = 0; j < keyValues->num_pairs; j++) {
    keyValues->pair_array[j] = malloc(sizeof(*keyValues->pair_array[j]));
    // Keys
    if (keyValues != NULL) {
      keyValues->pair_array[j]->key = malloc(sizeof(*keyValues->pair_array[j]->key));
      keyValues->pair_array[j]->key =
          copyString(lines[j], keyValues->pair_array[j]->key, lines[j][0], '=');
      // Values
      keyValues->pair_array[j]->value = malloc(sizeof(*keyValues->pair_array[j]->value));
      keyValues->pair_array[j]->value =
          copyString(lines[j], keyValues->pair_array[j]->value, '=', '\n');
    }
    else {
      fprintf(stderr, "Cant allocate memory for kv pairs\n");
      freeKVs(keyValues);
      free(lines);
      exit(EXIT_FAILURE);
    }
    free(lines[j]);
  }

  free(lines);
  return keyValues;
}

kvarray_t * readKVs(const char * fname) {
  // #1 - open file:
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Cant open the file.\n");
    return NULL;
  }
  // #2 - Read lines of file and split into keys and values
  kvarray_t * keyValues = readLines(f);

  // #3 Close files
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close this file %s\n", fname);
    freeKVs(keyValues);
    exit(EXIT_FAILURE);
  }
  return keyValues;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->num_pairs; i++) {
    free(pairs->pair_array[i]->key);
    free(pairs->pair_array[i]->value);
    free(pairs->pair_array[i]);
  }
  free(pairs->pair_array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //print keys and values
  for (int i = 0; i < pairs->num_pairs; i++) {
    printf("key = '%s' value = '%s'\n",
           pairs->pair_array[i]->key,
           pairs->pair_array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  // matching keys
  for (int i = 0; i < pairs->num_pairs; i++) {
    if (!strcmp(pairs->pair_array[i]->key, key)) {
      return pairs->pair_array[i]->value;
    }
  }
  return NULL;
}
