#include "Lindkedlist.h"
#include <iostream>
//
// Insert a node in a linkedlist
//
void LinkedList::insert(int value,
                        bool circular) {
  std::cout << "inserting value " << value << std::endl;
  Node *newNode = new Node(value);
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

void LinkedList::printReverse (Node *node) {
  if (node->getNext() == nullptr) {
    std::cout << node->getData() << " ";
    return;
  }
  printReverse(node->getNext());
  std::cout << node->getData() << " ";
}

Node* LinkedList::reverseListRecurs (Node *node) {
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