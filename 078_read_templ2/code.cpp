#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & v) {
  // this overload to the >> operator for many types of vectors
  s << "[";
  for (size_t i = 0; i < v.size(); i++) {
    if (i > 0) {
      s << ", ";
    }
    s << v[i];
  }
  s << "]";
  return s;
}

int main(void) {
  std::vector<int> v1;                // v1 is an empty "int" vector default init
  std::vector<std::vector<int> > v2;  // v2 is an empty "vector of vectors" of ints
  for (size_t i = 0; i < 4; i++) {
    v1.push_back(2 * i + 3);  //add at the end the numbers 3, 5, 7
    v2.push_back(v1);         // vector of 3, vector of 3,5, vector of 3,5,7...
    std::cout << v1 << std::endl;
  }
  std::cout << v2 << std::endl;
  return EXIT_SUCCESS;
}
