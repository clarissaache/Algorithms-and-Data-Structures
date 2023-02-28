#include <cstdlib>
#include <iostream>

class Animal {
 protected:
  const std::string name;

 public:
  Animal(std::string n) : name(n) {}  // constructor, not default
  virtual void speak() const = 0;     // its an ABSTRACT class
  virtual ~Animal() {                 //virtual destructor YAY!
    std::cout << "~Animal(" << name << ")" << std::endl;
  }
};
class Cat : public Animal {
 public:
  Cat(std::string n) : Animal(n) {  //uses the constructor from parent class
    speak();
  }
  virtual void speak() const {  // defined implementation of abstract member
    std::cout << name << " purrs." << std::endl;
  }
  virtual ~Cat() {
    std::cout << "~Cat(" << name << ")" << std::endl;
    speak();
  }
};
class Lion : public Cat {
 public:
  Lion(std::string n) : Cat(n) { speak(); }
  virtual void speak() const { std::cout << name << " roars." << std::endl; }

  virtual ~Lion() {
    std::cout << "~Lion(" << name << ")" << std::endl;
    speak();
  }
};

int main(void) {
  Cat cat1("Fluffy");   // prints:purrs.
  Lion lion1("Leon");   // prints purrs. and roars.
  Lion lion2("Aslan");  //prints again purrs. and roars.
  Animal * animals[3];
  animals[0] = &cat1;
  animals[1] = &lion1;
  animals[2] = &lion2;
  for (int i = 0; i < 3; i++) {
    animals[i]->speak();  //purrs. roars. purrs.
  }
  std::cout << "Don't forget your destructors!" << std::endl;  //lets see
  return EXIT_SUCCESS;
}
