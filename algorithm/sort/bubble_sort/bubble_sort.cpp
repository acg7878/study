#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// 思路：相邻的元素两两比较，如果前面的元素大于后面的元素，则交换这两个元素
void bubble_sort(std::vector<int>& arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    for (size_t j = 0; j < arr.size() - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void print_vector(const std::vector<int>& arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  std::cout << "Original array: " << std::endl;
  print_vector(arr);
  bubble_sort(arr);
  std::cout << "Sorted array: " << std::endl;
  print_vector(arr);
  return 0;
}