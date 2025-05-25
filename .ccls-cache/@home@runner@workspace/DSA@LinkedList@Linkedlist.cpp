#include "Lindkedlist.h"
#include <iostream>
//
// Insert a node in a linkedlist
//
void LinkedList::insert(int value,
                        bool circular) {
  std::cout << "inserting value " << value << std::endl;
  Node<int> *newNode = new Node<int>(value);
  //newNode->data = value;
  //newNode->next = nullptr;

  if (head == nullptr) {
    head = newNode;
    return;
  }

  auto list = head;
  while (list->getNext() != nullptr) {
    list = list->getNext();
  }

  list->setNext(newNode);
  
  if (circular) {
    list->setNext(head);
  }
  return;
}

//
// Remove a node from node
//
void LinkedList::remove(int value) {
  std::cout << "Removing value " << value << std::endl;
  if (head == nullptr) {
    std::cout << "list is empty" << std::endl;
    return;
  }
  auto prev = head;
  auto curr = head;
  while (curr != nullptr) {
    if (curr->getData() == value) {
      if (curr == head) {
        head = curr->getNext();
      } else {
        prev->setNext(curr->getNext());
      }
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->getNext();
  }
  return;
}

//
// Print a node data in forward order
//
void LinkedList::print() {
  if (head == nullptr) {
    std::cout << "list is empty" << std::endl;
    return;
  }
  auto list = head;
  while (list != nullptr) {
    std::cout << list->getData() << " ";
    list = list->getNext();
  }
  std::cout << std::endl;
  return;
}

//
// Check if list is circular
//
bool LinkedList::isCircular () {
  if (head == nullptr) {
    return false;
  }
  auto slowPtr = head;
  auto fastPtr = head->getNext();
  while (fastPtr != nullptr) {
    if (fastPtr == slowPtr) {
      return true;
    }
    slowPtr = slowPtr->getNext();
    if (fastPtr->getNext() != nullptr) {
      fastPtr = fastPtr->getNext()->getNext();
    } else {
      return false;
    }
  }

  return false;
}

//
// Find the middle element in a linkedlist
//
int LinkedList::findMid () {
  if (head == nullptr) {
    std::cout << "No element " << std::endl;
  }
  auto slowPtr = head;
  auto fastPtr = head;

  while ((fastPtr != nullptr) && (fastPtr->getNext() != nullptr)) {
    slowPtr = slowPtr->getNext();
    fastPtr = fastPtr->getNext()->getNext();    
  }

  return slowPtr->getData();
}

//
// Print linkedlist in reverse order
//
void LinkedList::printReverse (Node<int> *node) {
  if (node->getNext() == nullptr) {
    std::cout << node->getData() << " ";
    return;
  }
  printReverse(node->getNext());
  std::cout << node->getData() << " ";
}

//
// Reverse a linkedlist
//
Node<int>* LinkedList::reverseListRecurs (Node<int> *node) {
  if (node->getNext() == nullptr) {
    head = node;
    return node;
  } 
  
  auto prevNode = reverseListRecurs(node->getNext());
  prevNode->setNext(node);
  node->setNext(nullptr);
 // std::cout << " data: " << prevNode->getData();
  return node;
}

void LinkedList::setCircular () {
  if (head == nullptr) {
    return;
  }
  auto list = head;
  while (list->getNext() != nullptr) {
    list = list->getNext();
  }
  list->setNext(head);
}


#if 0
int main() {
  std::cout << "\nLinkded List Program\n";

  LinkedList list;

  list.remove(0);
  list.insert(12);
  list.print();
  list.remove(12);
  list.print();
  list.insert(12);
  list.insert(13);
  list.insert(14);
  list.insert(15, false);

  //list.insert(15, true);
  list.print();
#if 0
  list.remove(12);
  list.print();
  list.insert(12);
  list.print();
  list.remove(14);
  list.print();
  list.insert(14);
  list.print();
  list.remove(14);
  list.print();
  list.insert(14);
  list.print();
#endif
  std::cout << "List is circular: " << list.isCircular() << std::endl;
  std::cout << "Mid element in list: " << list.findMid() << std::endl;
  list.printReverse();
  std::cout << std::endl;
  list.reverseList();
  list.print();
  list.printReverse();
}
#endif