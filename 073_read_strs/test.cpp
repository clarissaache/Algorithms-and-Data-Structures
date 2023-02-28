#include <cstdlib>
#include <iostream>
#include <string>

std::string f(std::string x) {
  if (x == "") {
    return "";
  }
  char first = x[0];               //returns first character
  std::string rest = x.substr(1);  // returns chars of string after position 1
  // substr takes  a seconf arg that specifies how many chars after first to return
  std::cout << "first = " << first << " and rest = " << rest << std::endl;
  //std::endl adds a new line!
  std::string ans = f(rest);
  ans.push_back(first);  //contats at the end of string and icnreases length by 1
  std::cout << "ans = " << ans << std::endl;
  return ans;
}

int main(void) {
  std::string start("Apple");
  std::string ans = f(start);
  std::cout << "f(" << start << ") = " << ans << std::endl;
  return EXIT_SUCCESS;
}
