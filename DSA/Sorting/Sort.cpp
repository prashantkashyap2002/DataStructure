#include "Sort.h"
#if 1
int main() {
  class Sort sortClass;
  sortClass.insert(12);
  sortClass.insert(10);
  sortClass.insert(5);
  sortClass.insert(20);
  sortClass.insert(11);
  //sortClass.insert(10);
  // arr.bubbleSort();
  // arr.selectionSort();
  sortClass.print(sortClass.arr);
  //sortClass.mergeSort(sortClass.arr, 0, sortClass.arr.size() - 1);
  sortClass.quickSort(sortClass.arr, 0, sortClass.arr.size() - 1);
  sortClass.print(sortClass.arr);

}
#endif