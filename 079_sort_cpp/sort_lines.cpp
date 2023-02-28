#include <algorithm>  //sort
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char ** argv) {
  // PART A: Read from files
  if (argc != 1) {
    //For each input file:
    for (int f = 1; f < argc; f++) {
      // (1) Init a string for file name, a stream for file, and a vector to hold all lines
      std::vector<std::string> lines;
      std::string line;
      int i = 0;
      std::string file_name(argv[f]);
      std::fstream File;
      // (2) Open the filey
      File.open(file_name.c_str(), std::fstream::in);
      // (3) Get lines from file
      if (!File.is_open()) {
        std::cout << "Cant open the file" << file_name << std::endl;
      }
      else {
        while (std::getline(File, line)) {
          lines.push_back(line);  //allocates more space as vector grows
          i++;
        }
      }
      //(4) Sort lines:
      std::sort(lines.begin(), lines.end());

      //(5) Print Vector Lines Sorted
      std::cout << '\n';
      for (int j = 0; j < i; j++) {
        std::cout << lines[j] << std::endl;
      }
    }
    return EXIT_SUCCESS;
  }
  else {
    //PART B: Read from stdin
    std::vector<std::string> lines;
    std::string line;
    int i = 0;
    // Get lines from cin
    while (std::getline(std::cin, line)) {
      lines.push_back(line);
      i++;
    }
    // Print for testing
    std::sort(lines.begin(), lines.end());
    std::cout << '\n';
    for (int j = 0; j < i; j++) {
      std::cout << lines[j] << std::endl;
    }
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
