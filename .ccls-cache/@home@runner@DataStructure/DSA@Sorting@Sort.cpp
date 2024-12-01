#include "Sort.h"
#if 1
int main() {
  class Sort sortClass;
  
  sortClass.insert(15);
  sortClass.insert(3);
  sortClass.insert(25);
  sortClass.insert(20);
  sortClass.insert(2);
  sortClass.insert(10);
  sortClass.print(sortClass.arr);
  // sortClass.bubbleSort();
  // sortClass.selectionSort();
  sortClass.insertionSort();
  
  //sortClass.mergeSort(sortClass.arr, 0, sortClass.arr.size() - 1);
  //sortClass.quickSort(sortClass.arr, 0, sortClass.arr.size() - 1);
  //sortClass.heapSort(sortClass.arr, 0, sortClass.arr.size() - 1);
  sortClass.print(sortClass.arr);

}
#endif