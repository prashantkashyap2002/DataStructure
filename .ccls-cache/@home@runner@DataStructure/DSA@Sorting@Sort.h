#include <iostream>
#include <vector>
class Sort {
  public:
    Sort () {}
    ~Sort () {}

    void insert (int value) {
      arr.push_back(value);
    }

    void print () {
      for (auto it = arr.begin() ; it != arr.end(); it++) {
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
        for (int j = i+1; j < arr.size(); j++) {
          if (arr[i] > arr[j]) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
          }
        }
      }
    }

  private:
    std::vector<int> arr;
};