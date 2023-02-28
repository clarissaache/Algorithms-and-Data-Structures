#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64
#define DAYS_AVG 7

country_t parseLine(char * line) {
  country_t ans;
  // DEFINITION: This function captures the name and population of each country when provided as a string in the format: 'country,population'
  if (line[0] == '\n') {
    fprintf(stderr, "Data is NULL, can't do this!\n");
    exit(EXIT_FAILURE);
    // ans.name[0] = '\0';
    //ans.population = 0;
    //return ans;
  }
  // Is this a legit line?
  if ((strchr(line, ',') == NULL) || (strchr(line, '\0') == NULL)) {
    fprintf(stderr, "Nope! Needs to be a string of country, pop\n");
    exit(EXIT_FAILURE);
    //ans.name[0] = '\0';
    //ans.population = 0;
    //return ans;
  }
  // Read string for the name of the country
  size_t size = strlen(line);
  int red_flag = 1;
  size_t i = 0;
  while (i < size) {
    if (i > NAME_SIZE - 2) {
      fprintf(stderr, "No no no no. Name is too long.\n");
      exit(EXIT_FAILURE);
    }
    if (isalpha(line[i])) {
      ans.name[i] = line[i];
      red_flag = 0;
      i++;
    }
    if (line[i] == ' ') {
      ans.name[i] = ' ';
      i++;
    }
    if (line[i] == ',') {
      ans.name[i] = '\0';
      break;
    }
    if (!isalpha(line[i])) {  //When it's not letters
      ans.name[i] = '\0';
      red_flag = 1;
      break;
    }
  }
  if (red_flag == 1) {
    fprintf(stderr, "Country Name was not Captured! BYE\n");
    exit(EXIT_FAILURE);
    //ans.name[0] = '\0';
    //ans.population = 0;
    //return ans;
  }

  // Now, I'm going to save each number of the population count
  char copy[20] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                   '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
  char * p1 = &copy[0];
  char * p2 = strchr(line, ',');
  char * stop = strchr(copy, '\n');
  p2++;
  int total_digits = 0;
  red_flag = 1;
  while (*p2 != '\n' && p1 != stop) {
    if (total_digits > 20) {
      fprintf(
          stderr,
          "ERROR. There arent that many humans in the entire world. You are wrong.\n");
      ans.name[0] = '\0';
      ans.population = 0;
      exit(EXIT_FAILURE);
    }
    if (isdigit(*p2)) {
      *p1 = *p2;
      p1++;
      total_digits++;
      red_flag = 0;
    }
    if (!isdigit(*p2)) {
      red_flag = 1;
      break;
    }
    p2++;
  }
  *p1 = '\0';

  //red flag
  if (red_flag == 1) {
    fprintf(stderr, "Population was not written correctly! BYE\n");
    exit(EXIT_FAILURE);
    //ans.name[0] = '\0';
    //ans.population = 0;
    //return ans;
  }

  ans.population = atoi(copy);
  // EXIT_SUCCESS:
  return ans;
}

//
//
//

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //DEFINITION: This is a function that calculates the 7-day running average for time-series unsigned records
  if (data == NULL || n_days == 0) {
    fprintf(stderr, "Data is NULL, can't do this!");
    return;
  }
  unsigned * ptr = &data[0];
  unsigned * stop = &data[n_days];
  size_t g = 0;
  // Make sure dont go beyond the array size:
  while (ptr != stop) {
    double total = 0;
    unsigned * ptr2 = ptr;  // the second pointer "moves" after the first
    size_t a = 0;
    //Calculate Running Average:
    while (a < DAYS_AVG && ptr2 != stop) {
      total = total + (double)*ptr2;
      ptr2++;
      a++;
    }
    ptr++;
    if (g < n_days - 6) {
      avg[g] = total / (double)DAYS_AVG;
    }
    g++;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // DEFINITION: This function calculates the cummulative # of COVID cases per 100,000 people
  if (data == NULL || n_days == 0) {
    fprintf(stderr, "Data is NULL, can't do this!\n");
    exit(EXIT_FAILURE);
  }
  unsigned * stop = &data[n_days];
  for (size_t i = 0; i < n_days; i++) {
    unsigned * p = &data[0];
    double total = 0;
    for (size_t j = 0; j <= i; j++) {
      if (p != stop) {
        total += (double)p[j];
      }
    }
    cum[i] = total * 100000 / (double)pop;
  }
}

unsigned arrayMax(unsigned * array, size_t n) {
  unsigned * max = &array[0];
  unsigned max_index = 0;
  //This a slightly modified version of my arrayMax function in assignment 35
  // DEFINITION: Takes array and returns the idx of the max value of its elements
  if (array == NULL || n == 0) {
    printf("Data for this country is empty");
    exit(EXIT_FAILURE);
  }
  else {
    for (size_t i = 0; i < n; i++) {
      if (array[i] > *max) {
        max = &array[i];
        max_index = i;
      }
    }
  }

  return max_index;
}
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned maxes[n_countries];
  for (size_t i = 0; i < n_countries; i++) {
    size_t index = arrayMax(data[i], n_days);
    maxes[i] = data[i][index];
  }
  unsigned maxmax = arrayMax(maxes, n_countries);
  fprintf(stdout,
          "%s has the most daily cases with %u\n",
          countries[maxmax].name,
          maxes[maxmax]);
}
