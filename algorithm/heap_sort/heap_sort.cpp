#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

void print_vector(const std::vector<int>& arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void heapify(std::vector<int>& arr, int size, int index) {
  int largest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < size && arr[largest] < arr[left]) {
    largest = left;
  }
  if (right < size && arr[largest] < arr[right]) {
    largest = right;
  }
  if (largest != index) {
    std::swap(arr[largest], arr[index]);
    heapify(arr, size, largest);
  }
}

void heap_sort(std::vector<int>& arr) {
  for (int i = arr.size() / 2 - 1; i >= 0; i--)
    heapify(arr, arr.size(), i);

  for (int i = arr.size() - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

int main() {
  std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  std::cout << "Original array: " << std::endl;
  print_vector(arr);
  heap_sort(arr);
  std::cout << "Sorted array: " << std::endl;
  print_vector(arr);
  return 0;
}