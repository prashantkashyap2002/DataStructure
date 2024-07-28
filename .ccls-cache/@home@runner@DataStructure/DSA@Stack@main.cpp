#include "stack.h"

int main () {
  stack st;
  if (st.pop() == -1) {
    std::cout << "stack is empty" << std::endl;
  }
  st.push(10);
  st.push(20); 
  std::cout << "peek:" << st.peek() << std::endl;
  std::cout << "pop:" << st.pop() << std::endl;
  std::cout << "peek:" << st.peek() << std::endl;
  
  return 0;
}