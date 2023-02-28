#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //create the string with the output name of the file
  char * outfilename = malloc((strlen(inputName) + 8) * sizeof(*outfilename));
  strcpy(outfilename, inputName);
  strcat(outfilename, ".counts");
  return outfilename;
}
