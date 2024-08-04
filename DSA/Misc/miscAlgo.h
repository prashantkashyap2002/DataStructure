#include <iostream>
#include <vector>

int factorialRecursion(int num) {
  if (num <= 0)
    return 0;

  if (num == 1)
    return num;

  return (num * factorialRecursion(num - 1));
}

int factorialIterative(int num) {
  if (num <= 0)
    return 0;

  int result = 1;
  for (int i = 1; i <= num; i++) {
    result *= i;
  }
  return result;
}

int fibRecursion(int num) {
  if (num <= 1) {
    return 0;
  }
  if (num == 2) {
    return 1;
  }
  return (fibRecursion(num - 1) + fibRecursion(num - 2));
}

int fibIterative (int num) {
  if (num <= 1) {
    return 0;
  }
  if (num == 2) {
    return 1;
  }
  std::vector<int> arr{0,1};
  for (int i = 2; i <num; i++) {
    arr.push_back(arr[i-1] + arr[i-2]);
  }
  return arr[num-1];
}
