#include <iostream>

int factorialRecursion (int num) {
  if (num <=0) return 0;
  
  if (num == 1)
    return num;

  return (num * factorialRecursion(num-1));
}

int factorialIterative (int num) {
  if (num <=0) return 0;
  
  int result = 1;
  for (int i = 1; i <= num; i++) {
    result *= i;
  }
  return result;
}