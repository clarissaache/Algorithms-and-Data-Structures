#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largestIndex(int * freq) {
  int max = 0;
  for (int k = 0; k < 26; k++) {
    if (freq[k] > freq[max]) {
      max = k;
    }
  }
  return max;
}

int decrypt(FILE * f) {
  int c;
  int freq[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      // Now, on each occurence of a letter,
      //I get the index of where I store frequencies
      freq[c]++;
    }
  }
  int most_freq = largestIndex(freq);
  if (freq[most_freq] == 0) {
    return -1;
  }
  int ans = most_freq - ('e' - 'a');
  ans = (ans + 26) % 26;
  return ans;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: function takes one argument\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file");
    return EXIT_FAILURE;
  }

  //Decrypt e
  int answer = decrypt(f);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file");
    return EXIT_FAILURE;
  }
  if ((answer >= 26) || (answer < 0)) {
    fprintf(stderr, "Bad key error!");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "%d\n", answer);
  return EXIT_SUCCESS;
}
