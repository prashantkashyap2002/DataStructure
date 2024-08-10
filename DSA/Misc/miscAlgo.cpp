#include "miscAlgo.h"

#if 1
int main () {
  int num = 7;
  std::cout << "recursive-factorial of num:" << num << " is " << factorialRecursion(num) << std::endl;
  std::cout << "itertative-factorial of num:" << num << " is " << factorialIterative(num) << std::endl;

  std::cout << "Rec-fib of num:" << num << " is "<< fibRecursion(num) << std::endl;
  std::cout << "Iter-fib of num:" << num << " is "<< fibIterative(num) << std::endl;

  std::vector<int> arr{1,3,7,9,2};
  std::vector<int> ans{0,0};
  twoSum(arr, 16, ans);
  
  std::cout << "twoSum at " << ans[0] << " : " << ans[1] << std::endl;
}

#endif