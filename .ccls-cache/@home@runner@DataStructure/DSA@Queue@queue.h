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
      front = nullptr;
      back = nullptr;
    }

    ~Queue() {}
    void enqueue (T value) {
      queueNode<T> *node = new queueNode<T>(value);
      if (node == nullptr) {
        std::cout << "failed to allocate queueNode";
        return;
      }
      node->setNext(front);
      front = node;
      if (back == nullptr) {
        back = front;
      }
      std::cout << "enqued:" << front->getData() << std::endl;
    }

    T peek () {
      T retval{};
      if (back == nullptr) {
        std::cout << "queue is empty";
        return retval;
      }
      return back->getData();
    }

    void dequeue () {
      if (back == nullptr) {
        std::cout << "queue is empty" << std::endl;
        return;
      }
      std::cout << "dqueueing:" << back->getData() << std::endl;
      if (back == front) {
        free(back);
        back = front = nullptr;
        return;
      }
      queueNode<T> *tmp = front;
      while (tmp->getNext() != back) {
        tmp = tmp->getNext();
      }
      free(back);
      tmp->setNext(nullptr);
      back = tmp;
    }

  private: 
    queueNode<T> *front;
    queueNode<T> *back;
};

