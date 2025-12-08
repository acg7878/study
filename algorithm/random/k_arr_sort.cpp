#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using Element = std::pair<int, int>;

std::vector<int> k_arr_sort(std::vector<std::vector<int>>& arrs) {
  std::priority_queue<Element, std::vector<Element>, std::greater<Element>> pq;

  std::vector<int> pointers(arrs.size(), 0);

  for (size_t i = 0; i < arrs.size(); i++) {
    if (!arrs[i].empty()) {
      pq.emplace(arrs[i][0], i);
    }
  }
  std::vector<int> result;
  while (!pq.empty()) {
    auto pair = pq.top();
    pq.pop();

    int value = pair.first;
    int index = pair.second;

    result.push_back(value);
    pointers[index]++;
    if ((size_t)pointers[index] < arrs[index].size()) {
      pq.emplace(arrs[index][pointers[index]], index);
    }
  }
  return result;
}

int main() {
    std::vector<std::vector<int>> test_arrs = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };

    std::vector<int> sorted = k_arr_sort(test_arrs);
    std::cout << "result:";
    for (int num : sorted) {
        std::cout << num << " ";
    }
    // 输出：1 2 3 4 5 6 7 8 9
    return 0;
}