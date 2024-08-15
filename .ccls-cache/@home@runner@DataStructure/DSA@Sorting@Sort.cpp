#include "Sort.h"
#if 1
int main() {
  class Sort sortClass;
  sortClass.insert(12);
  sortClass.insert(10);
  sortClass.insert(5);
  sortClass.insert(20);
  sortClass.insert(11);
  sortClass.insert(10);
  // arr.bubbleSort();
  // arr.selectionSort();
  sortClass.print(sortClass.arr);
  std::vector<int> res(sortClass.arr.size());
  sortClass.mergeSort(sortClass.arr, res);
  sortClass.print(sortClass.arr);
  sortClass.print(res);
}
#endif