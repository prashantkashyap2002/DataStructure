#include <iostream>

template <class T> 
class node {
  public:
    node(int value) {
      node->data = value;
      node->next = nullptr
    }
  private:
    int data;
    node *next;
};

class stack {
public:
  stack() {}
  ~stack() {}
  void push(int value);
  int pop();
  int peek() {
    return top->data;
  }
private:
  node *top;
  node *head;
};