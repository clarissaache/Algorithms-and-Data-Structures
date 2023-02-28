#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "pages.hpp"

std::string getthePath(const char * dir, const char * fname) {
  /* This function concatenates a directory name and a file name with a '/' in between to create a path */
  std::stringstream ss;
  std::string full_name;
  ss << dir << '/' << fname;
  ss >> full_name;
  return full_name;
}

void saveNewPage(Page * page, std::string & line, const char * dir) {
  /* This function parses page lines from the story.txt file */
  size_t colon = line.find(':');
  page->page_num = atoi(line.substr(0, colon).c_str());
  std::string file_name = line.substr(colon + 1, line.size() - colon);
  page->file_name = getthePath(dir, file_name.c_str());
  std::string type = line.substr(line.find('@') + 1, 1);
  if (type[0] != 'N') {
    std::pair<std::string, int> c(type, 0);
    page->choices.push_back(c);
  }
}

std::vector<Page *> readInput(const char * dir, const char * file) {
  /* This function opens a story.txt (outline file) and reads each line, parsing them accordingly, and returning a vector of page objects (a story) */
  std::vector<Page *> story;
  std::string page_line;
  std::fstream File;
  std::string fname = getthePath(dir, file);
  File.open(fname.c_str(), std::fstream::in);
  if (!File.is_open()) {
    std::cerr << "Cant open the file " << fname << std::endl;
    exit(EXIT_FAILURE);
  }
  while (std::getline(File, page_line)) {
    if (page_line[0] != '\0') {
      if (strchr(page_line.c_str(), '@') != NULL) {
        Page * ans = new Page();
        // Parse page lines:
        saveNewPage(ans, page_line, dir);
        story.push_back(ans);
      }
      else {
        size_t colon1 = page_line.find(':');
        size_t colon2 = page_line.find(':', 2);
        size_t pnum = atoi(page_line.substr(0, colon1).c_str());

        if (story.size() != 0 && story.size() > pnum &&
            story[pnum]->page_num == pnum) {  // NEW
          // Parse choice lines:
          std::string choice = page_line.substr(colon2 + 1);
          int n = atoi(page_line.substr(colon1 + 1, colon2 - colon1).c_str());
          std::pair<std::string, int> c(choice, n);
          story[pnum]->choices.push_back(c);
        }
        else {
          std::cerr
              << "Its not you, its me.. JK lol. Your story is skipping page numbers!\n";
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  return story;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: need to provide name of directory with story\n";
    return EXIT_FAILURE;
  }
  std::vector<Page *> story = readInput(argv[1], "story.txt");
  Story story1(story);
  story1.printStory();
  EXIT_SUCCESS;
}
