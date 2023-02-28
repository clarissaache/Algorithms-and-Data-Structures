#include <cstdlib>
#include <iostream>
template<typename T>
class MyClass;
template<typename T>
std::ostream & operator<<(std::ostream & s, const MyClass<T> & x);

template<typename T>
class MyClass {
 private:
  T data;

 public:
  void setData(const T & d) { data = d; }  // method: set data

  template<typename A>  // method: f
  T f(const A & x) {
    return data + x;
  }
  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const MyClass<X> & x);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const MyClass<T> & x) {
  return s << x.data;
}

int main(void) {
  MyClass<std::string> s;       // class with data = empty string
  std::cout << s << std::endl;  // prints null ??

  MyClass<int> num;
  num.setData(42);  // but do we know what is in data rn?? It wasnt initialized to 0
  std::cout << num << std::endl;

  s.setData("Hello");

  std::cout << s.f<std::string>(" World") << std::endl;

  std::cout << num.f<double>(3.14) << std::endl;  // WHY IS IT NOT PRINTING A DOUBLE?
  /* I think is because num was initialized as type int, the "f" method returns an int 
   The double is the type of the parameter in f. Not the return type!*/

  MyClass<MyClass<int> > mc;  // now data's type is also MyClass (o.O) class inception!
  mc.setData(num);            //implicit type conversion?

  std::cout << mc << std::endl;

  return EXIT_SUCCESS;
}
