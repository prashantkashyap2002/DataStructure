#include "miscAlgo.h"

#if 1
int main () {
  int num = 7;
  std::cout << "recursive-factorial of num:" << num << " is " << factorialRecursion(num) << std::endl;
  std::cout << "itertative-factorial of num:" << num << " is " << factorialIterative(num) << std::endl;

  std::cout << "Rec-fib of num:" << num << " is "<< fibRecursion(num) << std::endl;
  std::cout << "Iter-fib of num:" << num << " is "<< fibIterative(num) << std::endl;
    
}

#endif