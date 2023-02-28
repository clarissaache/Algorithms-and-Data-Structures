#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class BadIndex : public std::exception {  // inheritance
 public:
  virtual const char * what() const throw() {  // I dont understand this
    return "Bad index\n";
  }
};

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}  // Only data Constructor
    Node(const T & d, Node * n) :
        data(d), next(n), prev(NULL) {}  // Data,Next Constructor
    Node(const T & d, Node * n, Node * p) :
        data(d), next(n), prev(p) {}  // All Constructor
  };
  Node * head;
  Node * tail;
  size_t size;
  //private recursive helper
  Node * remove_recursive(const T & data, Node * current, bool & flag) {
    //base case: empty list:
    if (current == NULL) {
      flag = 0;
      return NULL;
    }
    if (data == current->data) {
      Node * ans =
          current->next;  // fix "next" of previous node, can be NULL if its 1st node
      if (current->next !=
          NULL) {  //if its NOT the last item, fix "prev" of following node
        current->next->prev = current->prev;
      }
      if (tail == current) {   // if its the last item:
        tail = current->prev;  // make the tail what on current's "prev" (can be null)
        if (tail != NULL) {
          tail->next = NULL;
        }  //ugly
      }
      delete current;
      return ans;
    }
    if (current == tail) {
      flag = 0;
      return current;
    }
    current->next = remove_recursive(data, current->next, flag);
    return current;  //why?
  }

 public:
  // (7) DESTRUCTOR:
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    head = NULL;
    tail = NULL;
    size = 0;
  }
  // (1) DEFAULT CONSTRUCTOR
  LinkedList() : head(NULL), tail(NULL), size(0){};
  //(6) COPY CONSTRUCTOR:
  LinkedList(const LinkedList & rhs) {
    head = tail = NULL;
    Node * current = rhs.head;
    while (current != NULL) {
      addBack(current->data);
      current = current->next;
    }
    size = rhs.size;
  }
  // (8) OPERATOR=
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);  // cant destroy this nor the rhs!!
      size = rhs.size;
      // Save "this" head so its destroyed with temp
      Node * this_head = head;  //this head
      head = temp.head;
      temp.head = this_head;
      // Shave this tail so its destroyed with temp
      Node * this_tail = tail;
      tail = temp.tail;
      temp.tail = this_tail;
      // SWICHED THE LINKED LISTS! Now, temp can be destroyed...
    }
    return *this;
  }

  // (2) ADD FRONT
  void addFront(const T & item) {
    head = new Node(item, head, NULL);  //next is where head is pointing at
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  // (3) ADD BACK
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);  //prev points at what "tail" pointed at
    if (head == NULL) {
      head = tail;  //first item of list
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  // (4) REMOVE
  bool remove(const T & item) {
    bool flag = 1;
    head = remove_recursive(item, head, flag);
    if (flag == 1) {
      size--;
    }
    return flag;
  }
  // (5) INDEX OPERATOR
  T & operator[](int index) {
    Node * current = head;
    int i = 0;
    while (current != NULL && i < index) {  // find the node of index
      current = current->next;
      i++;
    }
    if (current == NULL) {
      throw BadIndex();
    }
    return current->data;
  }

  T & operator[](int index) const {
    Node * current = head;
    int i = 0;
    while (current != NULL && i < index) {  // find the node of index
      current = current->next;
      i++;
    }
    if (current == NULL) {
      throw BadIndex();
    }
    return current->data;
  }
  // (6) FIND
  int find(const T & item) const {
    Node * current = head;
    int i = 0;
    while (current != NULL) {
      if (current->data == item) {
        return i;
      }
      else {
        current = current->next;
        i++;
      }
    }
    //if head = current = null?
    if (head == NULL) {
      return -1;
    }
    return -1;
  }
  int getSize() const { return size; }

  friend class Tester;
};

#endif
