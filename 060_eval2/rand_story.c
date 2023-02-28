#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STEP 1 FUNCTIONS:

char ** readTemplate(FILE * f, size_t * i) {
  /* This function reads story templates using getline. 
  Templates can be multiple paragraphs or just one line*/
  char * line = NULL;
  char ** lines = NULL;
  size_t size = 0;
  *i = 0;
  while (getline(&line, &size, f) >= 0) {
    lines = realloc(lines, (*i + 1) * sizeof(*lines));
    lines[*i] = line;
    line = NULL;
    *i = *i + 1;
  }
  free(line);
  return lines;
}

void deleteCategory(char * category, const char * chosen, catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    if (!strcmp(cats->arr[i].name, category)) {
      // Found the category of the word to remove
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        if (!strcmp(cats->arr[i].words[j], chosen)) {
          // Found the word to remove
          cats->arr[i].n_words--;  // (1) reduce count of words
          free(cats->arr[i].words[j]);
          if (j == cats->arr[i].n_words) {
            // (2) word if its last in array
            break;
          }
          else {
            //If not: Make the pointer to the used word point at the next one:
            while (j < cats->arr[i].n_words) {
              cats->arr[i].words[j] = cats->arr[i].words[j + 1];
              j++;
            }
            //(3) maybe realloc so that the last pointer isnt dangling
            break;
          }
        }
      }
      break;
    }
  }
}
const char * findReplacement(char * category, catarray_t * cats) {
  const char * replacement = NULL;
  if (cats == NULL) {
    return replacement = chooseWord(category, cats);
  }
  // FIND REF
  if (!isalpha(category[0]) && strlen(category) < 2) {
    size_t N = atoi(category);
    if (N > cats->arr[0].n_words || N == 0) {
      fprintf(stderr, "WOOPS! ERROR: References in this story are wrong\n");
      exit(EXIT_FAILURE);
    }
    replacement = cats->arr[0].words[cats->arr[0].n_words - N];
    cats->arr[0].n_words++;
  }

  else {
    // NEW WORD
    replacement = chooseWord(category, cats);
    cats->arr[0].n_words++;
  }
  // Save it in the "used" storage
  cats->arr[0].words = realloc(cats->arr[0].words,
                               (1 + cats->arr[0].n_words) * sizeof(*cats->arr[0].words));
  cats->arr[0].words[cats->arr[0].n_words - 1] = strdup(replacement);

  return replacement;
}

char * replaceCategories(char * line, catarray_t * cats, int flag) {
  /* This function is going to copy char by char the line into another malloced array, when it finds the underscore, it will call the categories function to find a replacement and copy that string, after, it will continue copying the rest of the string */
  //
  //
  char * dest =
      malloc(strlen(line) * 2 * sizeof(*dest));  // NEED TO CHANGE THIS AFTER CATEGORY
  char * p_dest = &dest[0];
  char * p_source = &line[0];
  while (*p_source != '\0') {
    if (*p_source == '_') {
      *p_source = ' ';                  //(1) replace with a space
      char * stop = strchr(line, '_');  //(2) find where the key word ends
      char * category = malloc(stop - p_source);
      p_source++;  //(4) Get on the start of the category name
      size_t k = 0;
      while (p_source != stop) {  // (6) Copy every char
        category[k] = *p_source;
        p_source++;
        k++;
      }
      category[k] = '\0';
      // (7) Decide wether there is a reference or a new category, and find it.
      const char * replacement = findReplacement(category, cats);
      char * chosen = strdup(replacement);
      // (8) Add more space to destination array
      k = 0;
      while (*replacement != '\0') {
        *p_dest = *replacement;
        p_dest++;
        replacement++;
      }
      // Delete repeated words
      if (flag == 1) {
        deleteCategory(category, chosen, cats);
      }
      free(chosen);
      // Continue with the rest o the string (until _ is found again)
      *p_source = ' ';
      p_source = stop + 1;
      free(category);
    }
    *p_dest = *p_source;
    p_source++;
    p_dest++;
  }
  *p_dest = '\0';
  free(line);
  return dest;
}

// STEP 2 FUNCTIONS
catarray_t * saveCategories(char * key, char * value, catarray_t * cats) {
  /*In this function, for a key and value pair read from file,it will check if the name exist, add a new value under the name if it does. If not, it will add the new name to the categories array and its first value*/
  size_t i = 0;
  while (i < cats->n) {
    //search for the key:
    if (!strcmp(key, cats->arr[i].name)) {
      // if key is found, ADD NEW VALUE:
      cats->arr[i].words = realloc(
          cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(*cats->arr[i].words));
      cats->arr[i].words[cats->arr[i].n_words] = strdup(value);
      cats->arr[i].n_words++;
      return cats;
    }
    //keep searching...
    i++;
  }
  //...if key is not found, CREATE NEW CATEGORY:
  cats->n++;
  //(1) Expand array of cats for new category
  cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
  //(2) Save new category name
  cats->arr[i].name = strdup(key);
  cats->arr[i].n_words = 1;
  //(3) Allocate space for array of words
  cats->arr[i].words = malloc(cats->arr[i].n_words * sizeof(*cats->arr[i].words));
  //(4)Save first word
  cats->arr[i].words[0] = strdup(value);
  return cats;
}
char * saveKeyValue(char * line, int from, int to) {
  if (strchr(line, ':') == NULL) {
    fprintf(stderr, "This line does not have a colon\n");
    exit(EXIT_FAILURE);
  }
  char * start = strchr(line, from);
  char * stop = strchr(line, to);
  char * string = malloc((stop - start + 2) * sizeof(*string));
  if (stop == start) {  //special case for empty strings
    string[0] = '\0';
    return string;
  }
  if (*start == ':') {
    start++;
  }
  strncpy(string, start, stop - start);
  string[stop - start] = '\0';
  return string;
}

void freeStuff(catarray_t * cats) {
  for (size_t m = 0; m < cats->n; m++) {
    for (size_t n = 0; n < cats->arr[m].n_words; n++) {
      free(cats->arr[m].words[n]);
    }
    free(cats->arr[m].words);
    free(cats->arr[m].name);
  }
  free(cats->arr);
  free(cats);
}

// STEP 3 FUNCTIONS:
catarray_t * parseWords(char * file) {
  /* This function opens the file with WORDS, reads them, and saves them in the categories structure. After, it closes the file.*/
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    perror("Cannot open file: ");
    exit(EXIT_FAILURE);
  }
  // Read lines in file
  size_t i;
  char ** lines = readTemplate(f, &i);
  // Save Keys and Values where they belong
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 1;
  cats->arr = malloc(sizeof(*cats->arr));
  // Set the 1st to USED words:
  cats->arr[0].n_words = 0;
  char name[] = "UsedWordsInTHEpast";
  cats->arr[0].name = strdup(name);
  cats->arr[0].words = malloc(sizeof(*cats->arr[0].words));  //IDK if i need this
  //
  for (size_t j = 0; j < i; j++) {
    char * key = saveKeyValue(lines[j], lines[j][0], ':');
    char * value = saveKeyValue(lines[j], ':', '\n');
    cats = saveCategories(key, value, cats);
    free(key);
    free(value);
    free(lines[j]);
  }
  //free stuff:
  free(lines);

  //Close file with template
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }
  return cats;
}
