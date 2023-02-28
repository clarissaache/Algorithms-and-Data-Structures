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
  std::vector<std::pair<std::string, int> > page_variables;
  std::vector<std::pair<std::string, int> > choice_conditions;
  bool win;
  ~Page() {}
  Page() : page_num(0) {}
  void printPage();
  int readChoice(std::set<std::pair<std::string, int> > & collected);
  bool isEnd();
  void printPage(std::set<std::pair<std::string, int> > & collected);
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

void Page::printPage(std::set<std::pair<std::string, int> > & collected) {
  /* this methods is used to play the game with variables */
  /* Its still jsut a method to print a page in the format required */
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
      if (choice_conditions[j].first.empty()) {
        std::cout << j + 1 << ". " << choices[j].first << "\n";
      }
      else {
        if (collected.find(choice_conditions[j]) == collected.end()) {
          std::cout << j + 1 << ". <UNAVAILABLE>\n";
        }
        else {
          std::cout << j + 1 << ". " << choices[j].first << "\n";
        }
      }
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

int Page::readChoice(std::set<std::pair<std::string, int> > & collected) {
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
      std::cerr << "OOPS! " << badinput << " is not an integer number\n";
    }
  }
  // if input is within the bounds of choices of that page
  if (input > 0 && input <= choices.size()) {
    if (choice_conditions[input - 1].first.empty() ||
        collected.find(choice_conditions[input - 1]) != collected.end()) {
      return choices[input - 1].second;  // return the choice page number
    }
    else {
      std::cout << "That choice is not available at this time, please try again\n";
      return -1;
    }
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
  std::set<std::pair<std::string, int> > collected_vars;

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
    if (checkStory() != 1) {                    // 1 is good
      std::cerr << "This story is corrupt!\n";  // this line is never going to run lol
      exit(EXIT_FAILURE);
    }
    for (size_t k = 0; k < all_pages.size(); k++) {
      if (all_pages[k]->choices[0].first == "W") {
        win_pages.insert(all_pages[k]->page_num);
      }
    }
    // create bag of variables:
    for (size_t i = 0; i < all_pages.size(); i++) {
      for (size_t k = 0; k < all_pages[i]->page_variables.size(); k++) {
        std::pair<std::string, int> new_var(all_pages[i]->page_variables[k].first, 0);
        if (collected_vars.find(new_var) == collected_vars.end()) {
          collected_vars.insert(new_var);
        }
      }
    }
  }
  void printFramework() {
    /* Method to print the story outline (for testing)*/
    for (size_t i = 0; i < all_pages.size(); i++) {
      std::cout << all_pages[i]->page_num << "  ";
      std::cout << all_pages[i]->file_name << "\n";
      for (size_t k = 0; k < all_pages[i]->page_variables.size(); k++) {
        std::cout << "New Var: " << all_pages[i]->page_variables[k].first << " = "
                  << all_pages[i]->page_variables[k].second << "\n";
      }
      if (all_pages[i]->choices.size() >= 1) {
        for (size_t j = 0; j < all_pages[i]->choices.size(); j++) {
          std::cout << "\t" << all_pages[i]->choices[j].second << ". "
                    << all_pages[i]->choices[j].first << "\n";
          if (all_pages[i]->choice_conditions[j].first.length() != 0) {
            std::cout << "\t \t  On condition: "
                      << all_pages[i]->choice_conditions[j].first << " = "
                      << all_pages[i]->choice_conditions[j].second << "\n";
          }
        }
      }
    }
    std::cout << "--------------\n*Bag of All Story Variables*:\n";
    std::set<std::pair<std::string, int> >::iterator it = collected_vars.begin();
    while (it != collected_vars.end()) {
      std::cout << it->first << " " << it->second << "\n";
      ++it;
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
  void playGameWithVariables();
  bool isEmpty();
};

bool Story::isEmpty() {
  if (all_pages.size() == 0) {
    return 1;  //true
  }
  else {
    return 0;  //not empty
  }
}

bool Story::checkStory() {
  /* Method to checks (1) The choices match to a page that exists, (2) All pages are referenced by another page, (3) There is at least one win and wone lose page (4) Story is not empty */
  int win_flag = 0;
  int lose_flag = 0;
  int sum_of_elems = 0;

  if (isEmpty()) {
    return 0;  //1 is good
  }
  std::vector<int> checker(all_pages.size(), 0);  //vector of 0s
  checker[0] = 1;
  for (size_t i = 0; i < all_pages.size(); i++) {
    if (all_pages[i]->choices.size() >= 1) {
      for (size_t j = 0; j < all_pages[i]->choices.size(); j++) {
        if (!(all_pages[i]->choices[j].second <= (int)all_pages.size())) {
          std::cerr << "Choice on page " << i
                    << " takes you to a page that doesnt exist\n";
        }
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
  if (!(sum_of_elems == (int)all_pages.size())) {
    return 0;
  }
  if (!(win_flag == 1 && lose_flag == 1)) {
    return 0;
  }
  return 1;  //1 is good
}

void Story::playGame() {
  int current = 0;
  std::set<std::pair<std::string, int> > collected;
  int choice = 0;
  //Print page 0
  do {
    all_pages[current]->printPage();
    choice = all_pages[current]->readChoice(collected);
    while (choice == -1) {
      choice = all_pages[current]->readChoice(collected);
    }
    current = choice;
  } while (choice != -2);
}

void Story::playGameWithVariables() {
  int current = 0;
  int choice = 0;
  //Print page 0
  do {
    all_pages[current]->printPage(collected_vars);
    choice = all_pages[current]->readChoice(collected_vars);
    while (choice == -1) {
      choice = all_pages[current]->readChoice(collected_vars);
    }
    if (choice == -2) {
      break;
    }
    if (!all_pages[choice]->page_variables.empty()) {
      // for each variable to collect on a page
      for (size_t i = 0; i < all_pages[choice]->page_variables.size(); i++) {
        //add find it in the set:
        std::pair<std::string, int> new_var(all_pages[choice]->page_variables[i].first,
                                            0);
        std::set<std::pair<std::string, int> >::iterator it =
            collected_vars.find(new_var);
        //swap them (bc *it is const and I dont want to overload it)
        collected_vars.erase(it);
        collected_vars.insert(all_pages[choice]->page_variables[i]);
      }
    }
    current = choice;
  } while (choice != -2);
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
  /* overloading operator << to print vectors  */
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
