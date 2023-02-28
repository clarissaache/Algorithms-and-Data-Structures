#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    LinkedList<int> il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    LinkedList<int> il;
    int item = 3;
    int item2 = 4;
    il.addFront(item);  // add to empty list
    assert(il.head->data == item);
    assert(il.head->next == NULL);  // firt one on list, next should be null
    assert(il.head->prev == NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    il.addFront(item2);
    assert(il.head->data == item2);  //add on list with one node
    assert(il.tail->data == item);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == item);
    assert(il.tail->prev->data == item2);
    assert(il.head->next->prev->data == item2);
    assert(il.tail->prev->next->data == item);
    assert(il.head != il.tail);
    assert(il.getSize() == 2);
  }
  void testAddBack() {
    LinkedList<int> il;
    int item = 10;
    int item2 = 12;
    il.addBack(item);
    assert(il.head->data == item);
    assert(il.tail == il.head);
    assert(il.head->next == NULL);  // first one on list, next should be null
    assert(il.head->prev == NULL);
    assert(il.getSize() == 1);
    il.addBack(item2);
    assert(il.tail->data == item2);  // last item is item2
    assert(il.head->data == item);   //first item is item
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == il.head);
    assert(il.head->next->data == item2);
    assert(il.tail->prev->next->data == item2);
    assert(il.head->next->prev->data == item);
    assert(il.tail != il.head);
    assert(il.getSize() == 2);
  }
  // many more tester methods

  void testCopying() {
    LinkedList<int> il1;
    LinkedList<int> il2;
    int item = 10;
    int item2 = 12;
    int item3 = 13;
    int item4 = 15;
    il1.addBack(item2);
    il1.addFront(item);
    il1.addBack(item3);
    il1.addBack(item4);
    il2.addBack(21);
    il2.addBack(22);
    il2.addBack(23);
    // equal sign
    il2 = il1;
    assert(il1.head->data == il2.head->data);
    assert(il1.tail->data == il2.tail->data);
    assert(il1.getSize() == il2.getSize());
    assert(il1.head->next->data == il2.head->next->data);  //middle one
    assert(il1.head != il2.head);
    assert(il2.tail->next == NULL);
    assert(il2.head->next->next->prev->prev->prev == NULL);
    //copy constructor
    LinkedList<int> il3(il1);
    assert(il1.head->data == il3.head->data);
    assert(il1.tail->data == il3.tail->data);
    assert(il1.getSize() == il3.getSize());
    assert(il1.head->next->data == il3.head->next->data);  //middle one
    assert(il1.head->next != il3.head->next);              //deep copying
    assert(il3.tail->next == NULL);
  }
  void testRemove() {
    LinkedList<int> il;
    // empty list!
    assert(il.remove(10) == 0);
    il.addBack(11);
    il.addBack(12);
    il.addBack(13);
    il.addBack(14);
    //Not empty list:
    assert(il.remove(13) == 1);  //should work
    assert(il.remove(13) == 0);
    assert(il.find(13) == -1);
    assert(il.head->next->next->prev->prev->prev == NULL);
    assert(il.head->next->next->data == 14);
    //remove first:
    assert(il.remove(11) == 1);
    assert(il.find(11) == -1);
    assert(il.head->data == 12);
    assert(il.head->prev == NULL);
    //remove last:
    il.remove(14);
    assert(il.tail->data != 14);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail == il.head);  // only 12 remaining
    //remove only left
    il.remove(12);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    // check removed all
    LinkedList<int> il2;
    il2.addBack(12);
    il2.addBack(12);
    il2.addBack(12);
    il2.addFront(1);
    il2.addBack(1);
    il2.remove(12);
    assert(il2.find(12) == 1);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopying();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
