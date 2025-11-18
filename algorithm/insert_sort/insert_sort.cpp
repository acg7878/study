#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// 思路：将数组分为已排序和未排序两部分
// 每次将未排序部分的第一个元素插入到已排序部分的合适位置
void insert_sort(std::vector<int>& arr) {
  for (size_t i = 1; i < arr.size(); i++) {
    for (size_t j = i; j > 0; j--) {
      if (arr[j] < arr[j - 1]) {
        std::swap(arr[j], arr[j - 1]);
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
  insert_sort(arr);
  std::cout << "Sorted array: " << std::endl;
  print_vector(arr);
  return 0;
}