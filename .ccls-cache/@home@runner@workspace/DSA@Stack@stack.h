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
    
    T peek() {
      T retval{};
      if (top != nullptr) {
        return top->getData();
      } else {
        std::cout << "stack is empty";
        return retval;
      }
    }

  private:
    stNode<T> *top;
    stNode<T> *head;
};