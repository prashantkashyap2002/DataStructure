#include "queue.h"
#if 1
int main () {
  std::cout << "Queue:" << std::endl;
  Queue<int> intQueue;
  Queue<std::string> strQueue;
  intQueue.enqueue(10);
  std::cout << "intqueue peek:" << intQueue.peek() << std::endl;
  std::cout << "strQueue peek:" << strQueue.peek() << std::endl;

  intQueue.enqueue(20);
  std::cout << "intqueue peek:" << intQueue.peek() << std::endl;
  strQueue.enqueue("google");
  std::cout << "strQueue peek:" << strQueue.peek() << std::endl;

  intQueue.enqueue(30);
  std::cout << "intqueue peek:" << intQueue.peek() << std::endl;
  strQueue.enqueue("amazon");
  std::cout << "strQueue peek:" << strQueue.peek() << std::endl;

  intQueue.dequeue();
  strQueue.dequeue();
  std::cout << "intqueue peek:" << intQueue.peek() << std::endl;
  std::cout << "strQueue peek:" << strQueue.peek() << std::endl;

  intQueue.dequeue();
  strQueue.dequeue();
  std::cout << "intqueue peek:" << intQueue.peek() << std::endl;
  std::cout << "strQueue peek:" << strQueue.peek() << std::endl;

  intQueue.dequeue();
  strQueue.dequeue();
  std::cout << "intqueue peek:" << intQueue.peek() << std::endl;
  std::cout << "strQueue peek:" << strQueue.peek() << std::endl;
 
  return 1;
}
#endif