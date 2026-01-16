#include <vector>
#include <iostream>
int partition(std::vector<int>& arr,int start,int end) {
    int pivot = arr[start];
    while (start < end) {
        while (start < end && arr[end] > pivot) {
            end--;
        }
        arr[start] = arr[end];
        while (start < end && arr[start] < pivot) {
            start++;
        }
        arr[end] = arr[start];
    }
    arr[start] = pivot;
    return start;
}

void quick_sort(std::vector<int>& arr,int start,int end) {
    if (start >= end) {
        return;
    }
    int index = partition(arr, start, end);
    quick_sort(arr,start, index-1);
    quick_sort(arr, index+1, end);

}

void print_vector(const std::vector<int>& arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}
int main() {
  std::vector<int> arr = {7, 2, 3, 6, 5, 4, 1};
  std::cout << "Original array: " << std::endl;
  print_vector(arr);
  quick_sort(arr, 0, arr.size() - 1);
  std::cout << "Sorted array: " << std::endl;
  print_vector(arr);
  return 0;
}