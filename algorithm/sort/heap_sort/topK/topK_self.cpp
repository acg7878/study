#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::vector<int> generateRandomData(int count) {
  std::vector<int> data(count);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-1000000000, 1000000000);
  for (int i = 0; i < count; ++i) {
    data[i] = dis(gen);
  }
  return data;
}

void heapify(std::vector<int>& arr, int size, int index) {
  int smallest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < size && arr[smallest] > arr[left]) {
    smallest = left;
  }
  if (right < size && arr[smallest] > arr[right]) {
    smallest = right;
  }
  if (smallest != index) {
    std::swap(arr[smallest], arr[index]);
    heapify(arr, size, smallest);
  }
}

void build_heap(std::vector<int>& arr) {
  int n = arr.size();
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

std::vector<int> topK(const std::vector<int>& temp, int K) {
  if (temp.size() <= 0 || K <= 0 || K > temp.size()) {
    return {};
  }
  std::vector<int> arr(temp.begin(), temp.begin() + K);
  build_heap(arr);
  for (int i = K; i < temp.size(); i++) {
    if (arr[0] < temp[i]) {
      arr[0] = temp[i];
      heapify(arr, K, 0);
    }
  }
  std::sort(arr.begin(),arr.end(),std::greater<int>());
  return arr;
}

int main() {
  const int DATA_SIZE = 100000000;
  const int K = 50;

  std::cout << "Using manual min-heap:" << std::endl;
  std::vector<int> topK_manual = topK(generateRandomData(DATA_SIZE), K);
  std::cout << "The top " << K << " elements are: ";
  for (int val : topK_manual) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  return 0;
}