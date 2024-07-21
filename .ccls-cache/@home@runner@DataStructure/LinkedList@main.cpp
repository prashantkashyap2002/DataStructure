#include <iostream>
#include "Lindkedlist.h"

int main() {
  std::cout << "Linkded List Program\n";

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