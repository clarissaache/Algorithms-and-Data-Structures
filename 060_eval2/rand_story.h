#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

#include "provided.h"

//any functions you want your main to use
char ** readTemplate(FILE * f, size_t * i);
char * replaceCategories(char * line, catarray_t * cats, int flag);  //add flag
char * saveKeyValue(char * line, int from, int to);
catarray_t * saveCategories(char * key, char * value, catarray_t * cats);
catarray_t * parseWords(char * file);
void freeStuff(catarray_t * cats);

#endif
