#include <cstddef>
#include <iostream>
#include <vector>


void print_vector(const std::vector<int>& arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int partition(std::vector<int>& arr, int left, int right) {
  int pivot = arr[left];
  int i = left, j = right;
  while (i < j) {
    while (i < j && arr[j] >= pivot) {
      j--;
    }
    arr[i] = arr[j];
    while (i < j && arr[i] <= pivot) {
      i++;
    }
    arr[j] = arr[i];
  }
  arr[i] = pivot;
  return i;
}


void quick_sort(std::vector<int>& arr, int left, int right) {
  if (left >= right) {
    return;
  }
  int pivot = partition(arr, left, right);
  quick_sort(arr, left, pivot - 1);
  quick_sort(arr, pivot + 1, right);
}

int main() {
  std::vector<int> arr = {7,2,3,6,5,4,1};
  std::cout << "Original array: " << std::endl;
  print_vector(arr);
  quick_sort(arr, 0, arr.size() - 1);
  std::cout << "Sorted array: " << std::endl;
  print_vector(arr);
  return 0;
}
