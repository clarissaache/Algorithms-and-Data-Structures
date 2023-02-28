#include <cstdlib>
#include <iostream>

class AClass {
 private:
  int x;
  int y;

 public:
  AClass() : x(0), y(0) {
    std::cout << "Making AClass\n";  // default contrsuctor
  }
  AClass(int _x, int _y) : x(_x), y(_y) {
    std::cout << "Making AClass(" << x << "," << y << ")\n";  // other constructor
  }
  ~AClass() {
    std::cout << "Destroying AClass(" << x << "," << y << ")\n";  //destructor
  }
  int & max() {  // Function that returns a reference to x or y (the max)
    if (x > y) {
      return x;
    }
    return y;
  }
  void set(int _x, int _y) {  // Function that changes x and y to new values
    x = _x;
    y = _y;
  }
  int getX() const { return x; }  // Function that returns X
  int getY() const { return y; }  // Function that returns Y
};

AClass * someFunction(int a, int b) {
  AClass * x = new AClass(a + 2, b * 8);  //malloc a class
  AClass y(a * 4 - 3, b + 2);             // create another object, not malloced
  x->max() = y.max() - 3;  // the max of class x (x.x or x.y) = max of object y plus 3
  return x;
}

int main(void) {
  AClass a(3, 4);  // create a class, not default constructor x=3,y=4
  int & r =
      a.max();  // create a reference "r", = save the address of the max of x object "a"
  AClass * b = someFunction(r, 2);
  a.set(b->getY(), b->getX() - 3);
  delete b;
  r = 9;
  return EXIT_SUCCESS;
}
