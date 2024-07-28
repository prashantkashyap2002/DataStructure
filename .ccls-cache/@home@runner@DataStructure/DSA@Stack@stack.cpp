
#if 0
#include "stack.h"
template<typename T>
void Stack<T>::push(T value) {
  auto node = new stNode<T>(value);
  if (this->head == nullptr) {
    this->head = node;
    this->top = node;
  }
  this->top->setNext(node);
  this->top = node;
  return;
}

template <class T>
T Stack<T>::pop() {
  if (top != nullptr) {
    auto tmp = head;
    while (tmp->getNext() != top) {
      tmp = tmp->getNext();
    }

    int data = top->getData();
    free(top);
    top = tmp;
    return data;
  }
  std::cout << "stack is empty" << std::endl;
  return -1;
}

template <class T>
T Stack<T>::peek() {
  T retval;
  if (top != nullptr) {
    return top->getData();
  } else {
    std::cout << "stack is empty" << std::endl;
    return retval;
  }
}
#endif
#if 0
void Stack::push(std::string value) {
  stNode<std::string> *node = new stNode<std::string>(value);
  if (this->strHead == nullptr) {
    this->strHead = node;
    this->strTop = node;
  }
  this->strTop->setNext(node);
  this->strTop = node;
  return;
}

std::string Stack::pop(std::string val) {
  if (strTop != nullptr) {
    stNode<std::string> *tmp = strHead;
    while (tmp->getNext() != strTop) {
      tmp = tmp->getNext();
    }

    std::string data = strTop->getData();
    free(strTop);
    strTop = tmp;
    return data;
  }
  std::cout << "stack is empty" << std::endl;
  return NULL;
}
#endif