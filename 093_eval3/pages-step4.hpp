#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

/* The page object */

class Page {
 public:
  size_t page_num;
  std::string file_name;
  std::vector<std::pair<std::string, int> > choices;
  std::vector<std::pair<std::string, int> > variables;
  bool win;
  ~Page() {}
  Page() : page_num(0) {}
  void printPage();
  int readChoice();
  bool isEnd();
};
void Page::printPage() {
  /* Method to print a page in the format required */
  std::ifstream f(file_name.c_str());
  if (f.is_open()) {
    std::cout << f.rdbuf();
  }
  else {
    perror("Usage: Can't open the page file\n");
    exit(EXIT_FAILURE);
  }
  if (choices.size() >= 1 && choices[0].first != "W" && choices[0].first != "L") {
    std::cout << "\nWhat would you like to do?\n\n";
    for (size_t j = 0; j < choices.size(); j++) {
      std::cout << j + 1 << ". " << choices[j].first << "\n";
    }
  }
  else {
    if (choices[0].first == "W") {
      std::cout << "\nCongratulations! You have won. Hooray!\n";
    }
    if (choices[0].first == "L") {
      std::cout << "\nSorry, you have lost. Better luck next time!\n";
    }
  }
}

int Page::readChoice() {
  /* This function reads the choice option from the user*/
  if (this->isEnd()) {
    return -2;
  }
  unsigned input;
  std::cin >> input;  // read input from user
  if (!std::cin.good()) {
    std::cin.clear();
    std::string badinput;
    std::cin >> badinput;
    if (!std::cin.good()) {
      std::cerr << "Cannot read anything from cin! This place sucks!\n";
    }
    else {
      std::cerr << "OOPS! " << badinput << "is not an integer number\n";
    }
  }
  // if input is within the bounds of choices of that page, return the choice page:
  if (input > 0 && input <= choices.size()) {
    return choices[input - 1].second;
  }
  else {
    std::cout << "That is not a valid choice, please try again\n";
    return -1;
  }
}
bool Page::isEnd() {
  if (choices[0].first == "W" || choices[0].first == "L") {  // if either of these is true
    return 1;                                                // this page is an end page
  }
  else {
    return 0;
  }
}

/* The Story object is a container of pages
´´´´´´´´´´´´´´´´´´´´´´¶¶¶¶¶¶¶¶¶
´´´´´´´´´´´´´´´´´´´´¶¶´´´´´´´´´´¶¶
´´´´´´¶¶¶¶¶´´´´´´´¶¶´´´´´´´´´´´´´´¶¶
´´´´´¶´´´´´¶´´´´¶¶´´´´´¶¶´´´´¶¶´´´´´¶¶
´´´´´¶´´´´´¶´´´¶¶´´´´´´¶¶´´´´¶¶´´´´´´´¶¶
´´´´´¶´´´´¶´´¶¶´´´´´´´´¶¶´´´´¶¶´´´´´´´´¶¶
´´´´´´¶´´´¶´´´¶´´´´´´´´´´´´´´´´´´´´´´´´´¶¶
´´´´¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´´´´´´´´´´´´´´´¶¶
´´´¶´´´´´´´´´´´´¶´¶¶´´´´´´´´´´´´´¶¶´´´´´¶¶
´´¶¶´´´´´´´´´´´´¶´´¶¶´´´´´´´´´´´´¶¶´´´´´¶¶
´¶¶´´´¶¶¶¶¶¶¶¶¶¶¶´´´´¶¶´´´´´´´´¶¶´´´´´´´¶¶
´¶´´´´´´´´´´´´´´´¶´´´´´¶¶¶¶¶¶¶´´´´´´´´´¶¶
´¶¶´´´´´´´´´´´´´´¶´´´´´´´´´´´´´´´´´´´´¶¶
´´¶´´´¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´´´´´´´´´´¶¶
´´¶¶´´´´´´´´´´´¶´´¶¶´´´´´´´´´´´´´´´´¶¶
´´´¶¶¶¶¶¶¶¶¶¶¶¶´´´´´¶¶´´´´´´´´´´´´¶¶
´´´´´´´´´´´´´´´´´´´´´´´¶¶¶¶¶¶¶¶¶¶¶
 */

class Story {
  std::vector<Page *> all_pages;
  std::vector<std::vector<int> > matrix;  // adjecency matrix
  std::set<int> win_pages;

 public:
  Story(){};
  ~Story() {
    for (size_t i = 0; i < all_pages.size(); i++) {
      delete all_pages[i];
    }
  }
  Story(Story & rhs) {
    /* Copy constructor */
    std::vector<Page *>::iterator it = rhs.all_pages.begin();
    while (it != rhs.all_pages.end()) {
      all_pages.push_back(*it);
    }
    ++it;
    win_pages = rhs.win_pages;
  }
  Story & operator=(Story & rhs) {
    /* Assign operator */
    win_pages = rhs.win_pages;
    if (this != &rhs) {
      all_pages.clear();
      std::vector<Page *>::iterator it = rhs.all_pages.begin();
      while (it != rhs.all_pages.end()) {
        all_pages.push_back(*it);
        ++it;
      }
    }
    return *this;
  }
  Story(std::vector<Page *> s) : all_pages(s) {
    if (checkStory() == 1) {
      //std::cout << "Checked the story and its good!\n";
    }
    // build set of winning pages of off all_pages
    for (size_t k = 0; k < all_pages.size(); k++) {
      if (all_pages[k]->choices[0].first == "W") {
        win_pages.insert(all_pages[k]->page_num);
      }
    }
  }
  void printFramework() {
    /* Method to print the story outline (for testing)*/
    for (size_t i = 0; i < all_pages.size(); i++) {
      std::cout << all_pages[i]->page_num << "  ";
      std::cout << all_pages[i]->file_name << "\n";
      if (all_pages[i]->choices.size() >= 1) {
        for (size_t j = 0; j < all_pages[i]->choices.size(); j++) {
          std::cout << "\t" << all_pages[i]->choices[j].second << ". "
                    << all_pages[i]->choices[j].first << "\n";
        }
      }
    }
  }
  void printStory() {
    /* Method to print all pages of the story */
    for (size_t i = 0; i < all_pages.size(); i++) {
      std::cout << "Page " << all_pages[i]->page_num << "\n==========\n";
      all_pages[i]->printPage();
    }
  }
  bool checkStory();
  void playGame();
  void createAdjMatrix();
  void printMatrix();
  void printPath(std::vector<int> & v);
  void depthFirstSearch();
};

bool Story::checkStory() {
  /* Method to checks (1) The choices match to a page that exists, (2) All pages are referenced by another page, (3) There is at least one win and wone lose page */
  std::vector<int> checker(all_pages.size(), 0);  //vector of 0s
  int win_flag = 0;
  int lose_flag = 0;
  int sum_of_elems = 0;

  checker[0] = 1;
  for (size_t i = 0; i < all_pages.size(); i++) {
    if (all_pages[i]->choices.size() >= 1) {
      for (size_t j = 0; j < all_pages[i]->choices.size(); j++) {
        assert(all_pages[i]->choices[j].second <= (int)all_pages.size());
        checker[all_pages[i]->choices[j].second] = 1;
      }
    }
    if (all_pages[i]->choices.size() == 1) {
      if (all_pages[i]->choices[0].first == "W") {
        win_flag = 1;
      }
      if (all_pages[i]->choices[0].first == "L") {
        lose_flag = 1;
      }
    }
  }
  for (std::vector<int>::iterator it = checker.begin(); it != checker.end(); ++it) {
    sum_of_elems += *it;
  }
  assert(sum_of_elems == (int)all_pages.size());
  assert(win_flag == 1 && lose_flag == 1);
  return 1;
}

void Story::playGame() {
  int current = 0;
  int choice = 0;
  //Print page 0
  while (choice != -2) {
    all_pages[current]->printPage();
    choice = all_pages[current]->readChoice();
    while (choice == -1) {
      choice = all_pages[current]->readChoice();
    }
    current = choice;
  }
}

void Story::createAdjMatrix() {
  /* This method creates the adjecency matrix and fills it out with the adjecent pages*/
  for (size_t i = 0; i < all_pages.size(); i++) {
    std::vector<int> vec(all_pages.size(), 0);  //create vector of zeros
    matrix.push_back(vec);
  }
  // Fill it with the right stuff:
  for (size_t i = 0; i < all_pages.size(); i++) {
    if (all_pages[i]->choices.size() >= 1) {  // all pages must have choices or W/L, tho
      for (size_t j = 0; j < all_pages[i]->choices.size(); j++) {
        matrix[i][all_pages[i]->choices[j].second] = 1;
      }
    }
  }
}
void Story::printMatrix() {
  //Print it adjecency matrix (for testing)
  for (size_t i = 0; i < all_pages.size(); i++) {
    std::cout << "\n";
    for (size_t j = 0; j < all_pages.size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
  }
  std::cout << "\n";
}
template<typename S>
std::ostream & operator<<(std::ostream & os, const std::vector<S> & vector) {
  /* overloading operator << to print vectors */
  for (size_t i = 0; i < vector.size(); i++) {
    os << vector[i] << " ";
  }
  os << "\n";
  return os;
}

void Story::printPath(std::vector<int> & v) {
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i];
    if (v[i] == v.back()) {
      break;
    }
    for (size_t j = 0; j < all_pages[v[i]]->choices.size(); j++) {
      if (all_pages[v[i]]->choices[j].second == v[i + 1]) {
        std::cout << "(" << j + 1 << "),";
        break;
      }
    }
  }
  std::cout << "(win)\n";
}
void Story::depthFirstSearch() {
  //dfs algorithm
  bool not_found = 1;
  std::stack<std::vector<int> > todo;
  std::set<int> visited;
  std::vector<int> current_path;
  int current_node;
  // Starting from page 0 always
  std::vector<int> from(1, 0);
  todo.push(from);
  // As long as to-do list is not empty:
  while (!todo.empty()) {
    current_path = todo.top();
    current_node = current_path.back();
    todo.pop();
    if (win_pages.find(current_node) != win_pages.end()) {
      not_found = 0;
      printPath(current_path);
      win_pages.erase(current_node);
    }
    if (visited.find(current_node) == visited.end()) {
      visited.insert(current_node);
      for (size_t i = 0; i < all_pages.size(); i++) {
        if (matrix[current_node][i] == 1) {
          current_path.push_back(i);
          todo.push(current_path);
          current_path.pop_back();
        }
      }
    }
  }
  if (not_found == 1) {
    std::cout << "No valid path exists\n";
  }
}
