#include <iostream>
#include <vector>
#include <unordered_map>

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

void twoSum (std::vector<int> arr, int target, std::vector<int>& res) {
  std::unordered_map<int,int> comp;
  int i = 0;
  while (i < arr.size()) {
    auto complement = target - arr[i];
    auto it = comp.find(complement);
    //std::cout << "i:" << i << " val:" << arr[i] << " comp:" << complement << std::endl;
    if (it != comp.end()) {
      std::cout << "found the target at " << it->second << " " << i << std::endl;
      res[0] = i;
      res[1] = it->second;
      return;
    }
    comp.insert({arr[i], i});
    i++;
  }
#if 0
  for (auto it = comp.begin(); it != comp.end(); it++) {
    std::cout << "1st:" << it->first << " ,2nd:" << it->second << std::endl;
  }
#endif
  return;
}