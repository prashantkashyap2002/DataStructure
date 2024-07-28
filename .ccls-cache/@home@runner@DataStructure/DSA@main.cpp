#include <iostream>
#include "LinkedList/Lindkedlist.h"
#include "Stack/stack.h"

int main() {

  Stack<int> st;
  Stack<std::string> stStr;
  std::cout << "stack Program\n";

  std::cout << "peek " << st.peek() << std::endl;
  std::cout << "str::peek " << stStr.peek() << std::endl;

  st.push(10);
  stStr.push("google");
  stStr.push("amazon"); 
  st.push(20); 
  std::cout << "peek:" << st.peek() << std::endl;
  st.pop();
  std::cout << "peek:" << st.peek() << std::endl;

  std::cout << "str::peek:" << stStr.peek() << std::endl;
  stStr.pop();
  std::cout << "str::peek:" << stStr.peek() << std::endl;
    
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