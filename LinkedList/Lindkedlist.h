
// Forward declaration
class LinkedList;

template <typename T>
class Node {
public:
  Node<T> (T value) {
    this->data = value;
    this->next = nullptr;
  }
  ~Node<T> () {}
  T& getData () {
    return this->data;
  }

  Node<T>* getNext () {
    return this->next;
  }

  void setNext (Node<T>* node) {
    this->next = node;
  }

private:
  T data;
  Node *next;
};

class LinkedList {
public:
  LinkedList() { head = nullptr; };
  ~LinkedList(){};
  void insert(int value, bool circular = false);
  void remove(int);
  void print();
  bool isCircular();
  int findMid();
  void printReverse () {
    printReverse(head);
  }
  void reverseList () {
    reverseListRecurs(head);
  }

private:
  Node<int> *head;
  void setCircular();
  void printReverse(Node<int> *node);
  Node<int>* reverseListRecurs(Node<int> *node);
};