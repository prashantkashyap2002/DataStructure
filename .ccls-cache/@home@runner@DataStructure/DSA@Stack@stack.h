#include <iostream>

template <typename T> 
class stNode {
  public:
    stNode(T value) {
      this->data = value;
      this->next = nullptr;
    }
    T& getData() { return data;}
    void setNext(stNode<T> *node) { this->next = node;}
    stNode<T>* getNext() { return this->next;}

  private:
    T data;
    stNode<T> *next;
};

template <typename T>
class Stack {
  public:
    Stack() {
      head = nullptr;
      top = nullptr;
    }
    ~Stack() {}

    void push(T value) {
      auto node = new stNode<T>(value);
      if (this->head == nullptr) {
        this->head = node;
        this->top = node;
      }
      this->top->setNext(node);
      this->top = node;
      return;
    }

  //  void push(std::string value);
    void pop() {
      if (top != nullptr) {
        stNode<T> *tmp = head;
        while (tmp->getNext() != top) {
          tmp = tmp->getNext();
        }
        free(top);
        top = tmp;
        return;
      }
      std::cout << "stack is empty" << std::endl;
    }
    //std::string pop(std::string val);
    T peek() {
      T retval{};
      if (top != nullptr) {
        return top->getData();
      } else {
        std::cout << "stack is empty";
        return retval;
      }
    }

#if 0
    std::string peek(std::string val = NULL) {
      if (strTop != nullptr) {
        return strTop->getData();
      } else {
        std::cout << "stack is empty";
        return NULL;
      }
    };
#endif

  private:
    stNode<T> *top;
    stNode<T> *head;
//    stNode<std::string> *strTop = nullptr;
//    stNode<std::string> *strHead = nullptr;
};