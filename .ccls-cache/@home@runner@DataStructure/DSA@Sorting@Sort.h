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
    mergeSort (std::vector<int>& list, std::vector<int>& res) {
      //std::cout<< "size of the Arr:" << list.size() << std::endl;
      if (list.size() <= 1) {
        return;
      }

      int mid = list.size()/2;
      std::vector<int> leftList;

      for (int i=0; i < mid; i++) {
        leftList.push_back(list[i]);
      }
      mergeSort(leftList, res);
      
      std::vector<int> rightList;
      for (int i = mid; i < list.size(); i++) {
          rightList.push_back(list[i]);
      }
      mergeSort(rightList, res);
      std::cout << "leftArr: ";
      print(leftList);

      std::cout << " rightArr:";
      print(rightList);
      
      merge(leftList, rightList, res);
      print(rightList);
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
    void merge (std::vector<int>& listl, std::vector<int>& listr, std::vector<int>& res) {
      
      auto lsize = listl.size();
      auto rsize = listr.size();
      std::cout << "merge- lsize:" << lsize << " rsize:" << rsize << std::endl;
      int i = 0;
      int j = 0;
      int k = 0;
      while (k < lsize + rsize) {
        if ((i == lsize) && (j < rsize)) {
          res[k++] = listr[j++];
        } else if (j == rsize && i < lsize) {
          res[k++] = listl[i++];
        } else {
          if (listl[i] > listr[j]) {
            res[k++] = listr[j++]; 
          } else {
            res[k++] = listl[i++];
          }
        }
        //std::cout<< " " << res[k-1];
      }
      for (i = 0; i < lsize; i++) {
        listl[i] = res[i];
      }
      j = 0;
      for (i = lsize; i < k; i++) {
        listr[j++] = res[i];
      }
      print(listl);
      print(listr);
      std::cout << " SortedArr:";
      print(res);
      return;
    }
};