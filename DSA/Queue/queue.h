#include <iostream>

template <typename T>
class queueNode {
  public:
    queueNode (T value) {
      this->data = value;
      this->next = nullptr;
    }

    T& getData () {
      return data;
    }
    void setNext (queueNode<T> *node) {
      next = node;
    }

    queueNode<T> *getNext () {
      return next;
    }
  private:
    T data;
    queueNode<T> *next;
};

template <typename T>
class Queue {
  public:
    Queue() {
      head = nullptr;
      top = nullptr;
    }

    ~Queue() {}
    void enqueue (T value) {
      queueNode<T> *node = new queueNode<T>(value);
      if (node == nullptr) {
        std::cout << "failed to allocate queueNode";
        return;
      }
      node->setNext(head);
      head = node;
      if (top == nullptr) {
        top = head;
      }
      std::cout << "enqued:" << head->getData() << std::endl;
    }

    T peek () {
      T retval{};
      if (top == nullptr) {
        std::cout << "queue is empty";
        return retval;
      }
      return top->getData();
    }

    void dequeue () {
      if (top == nullptr) {
        std::cout << "queue is empty" << std::endl;
        return;
      }
      std::cout << "dqueueing:" << top->getData() << std::endl;
      if (top == head) {
        free(top);
        top = head = nullptr;
        return;
      }
      queueNode<T> *tmp = head;
      while (tmp->getNext() != top) {
        tmp = tmp->getNext();
      }
      free(top);
      tmp->setNext(nullptr);
      top = tmp;
    }

  private: 
    queueNode<T> *head;
    queueNode<T> *top;
};

