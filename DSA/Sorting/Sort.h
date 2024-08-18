#include <iostream>
#include <vector>
using namespace std;
class Sort {
  public:
    Sort () {}
    ~Sort () {}

    void insert (int value) {
      arr.push_back(value);
    }

    void print (std::vector<int> &array) {
      for (auto it = array.begin() ; it != array.end(); it++) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;
    }

    void bubbleSort () {
      for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size() - 1; j++) {
          if (arr[j] > arr[j+1]) {
            int tmp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = tmp;
          }
        }
      }
    }

    void selectionSort () {
      for(int i = 0; i < arr.size(); i++) {
        for (int j = 1; j < i; j++) {
          if (arr[i] > arr[j]) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
          }
        }
      }
    }

    void insertionSort () {
      for (int i = 1; i < arr.size(); i++) {
        for (int j = 0; j < i; j++) {
          
        }
      }
    }

    void
    mergeSort (std::vector<int>& list, int l, int r) {
      //std::cout<< "l:" << l << " r:" << r << std::endl;
      if (l >= r) {
        return;
      }

      int mid = l + (r - l)/2;
      
      mergeSort(list, l, mid);
      mergeSort(list, mid + 1, r);
      merge(list, l, mid, r);
      print(list);
      return;
    }

    void quickSort (std::vector<int> &list, int low, int high) {
      if (low >= high) return;
      std::cout << "low:" << low << " high:" << high << std::endl;
      int pivot = high;
      for (int i = low; i <= high; i++) {
        if (i == pivot) continue;
        else if (i < pivot) {
          // Iterating through left side to pivot
          if (list[i] > list[pivot]) {
            std::swap(list[i], list[pivot]);
            pivot = i;
          } 
        } else {
          // Iterating through right side to pivot
          if (list[i] < list[pivot]) {
            std::swap(list[i], list[pivot]);
            pivot = i;
          }
        }
      }
      print(list);
      quickSort(list, low, pivot - 1);
      quickSort(list, pivot+1, high);
      
      return;
    }

    void heapSort (std::vector<int> &list, int low, int high) {
      for (; low < high; low++) {
        maxHeap(list, high-low);
        std::swap(list[0], list[high-low]);
        //print(list);
      }
      return;
    }

    std::vector<int> arr;
  private:
    void merge (std::vector<int>& list, int l, int mid, int r) {
      //std::cout<< "merge l:" << l << " r:" << r << std::endl;
      int i = 0;
      int j = 0;
      int lsize = mid - l + 1;
      int rsize = r - mid;
      int k = l; // no of item in list
      // llist - list[l:mid-1]
      // rlist - list[mid:r]
      std::vector<int> llist(list.begin() + l, list.begin() + l + lsize);
     // for (i = 0; i < lsize; i++) {
     //   llist[i] = list[l+i];
     // }
      std::vector<int> rlist(list.begin() + mid + 1, list.begin() + mid + 1 + rsize);
     // std::vector<int> rlist(rsize);
     // for (i = 0; i < rsize; i++) {
     //   rlist[i] = list[mid+i + 1];
     // }
      i = 0;
      while (i < lsize && j < rsize) {
        if (llist[i] > rlist[j])
        {
          // rlist element is smaller
          list[k++] = rlist[j++];
        } else {
          // llist element is smaller
          list[k++] = llist[i++];
        }
      }
      if (i < lsize) {
        // copy remaining elements from llist
        while (i < lsize) {
          list[k++] = llist[i++];
        } 
      } else {
        // copy remaining elements from rlist
        while (j < rsize) {
          list[k++] = rlist[j++];
        } 
      }
     
      return;
    }

    void maxHeap (std::vector<int> &list, int high) {
      // left child = i + 1
      // right child = i + 2;
      // parent = i
      bool reheap = false;
      for (int i = 0; i+2 <= high; i = i + 3) {
        int left = (int)(i + 1);
        int right = (int)(i + 2);
        if (list[i] < list[left]) {
          // left child is larger so swap with parent
          std::swap(list[i], list[left]);
        }
        if (list[i] < list[right]) {
          // Right child is larger so swap the child with parent
          std::swap(list[i], list[right]);
        }
        //std::cout << "max:" << list[i] << std::endl;
      } 
      
      for (int i = 0; i <= high; i = i + 3) {
        // root is always the max
        if (list[0] < list[i]) {
          reheap = true;
          std::swap(list[0], list[i]);
        } 
        
      }

      if (reheap) {
        // Since change in parent so rerun it again to make sure
        // parent is always bigger than children
        maxHeap(list, high);
      }
     // std::cout << "maxHeap:" << list[0] << " high" << high << " - ";
     // print(list);
     // std::cout << std::endl;
      return;
    }
};