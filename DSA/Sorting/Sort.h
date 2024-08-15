#include <iostream>
#include <vector>
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

    void quickSort () {
      return;
    }

    void heapSort () {
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
        while (i < lsize) {
          list[k++] = llist[i++];
        } 
      } else {
        while (j < rsize) {
          list[k++] = rlist[j++];
        } 
      }
     
      return;
    }
};