
// Forward declaration
class Node;
class LinkedList;

class Node {
public:
  Node (int value) {
    this->data = value;
    this->next = nullptr;
  }
  ~Node () {}
  int getData () {
    return this->data;
  }

  Node* getNext () {
    return this->next;
  }

  void setNext (Node* node) {
    this->next = node;
  }

private:
  int data;
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
  Node *head;
  void setCircular();
  void printReverse(Node *node);
  Node* reverseListRecurs(Node *node);
};