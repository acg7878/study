// 找到一个元素集合中，出现频次前k的元素

#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using Pair = std::pair<int, int>;
// struct Compare {
//   bool operator()(const Pair& a, const Pair& b) { return a.first > b.first; }
// };
std::vector<int> findK(const std::vector<int>& arr, int k) {
  std::unordered_map<int, int> freq_map;  // 元素，频率
  for (int num : arr) {
    freq_map[num]++;
  }

  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

  for (auto it = freq_map.begin(); it != freq_map.end(); it++) {
    int num = it->first;
    int freq = it->second;
    if (pq.size() < k) {
      pq.emplace(freq, num);
    } else {
      auto node = pq.top();
      if (node.first < it->second) {
        pq.pop();
        pq.emplace(it->second, it->first);
      }
    }
  }

  std::vector<int> ans;
  while (!pq.empty()) {
    ans.push_back(pq.top().second);
    pq.pop();
  }
  return ans;
}

int main() {
  std::vector<int> test = {1,  1, 1, 1,  1, 1,  1, 323, 23,   23, 3,
                           3,  3, 2, 3,  3, 3,  5, 21,  5423, 54, 24,
                           23, 1, 1, 14, 5, 55, 5, 55,  55,   5,  5};

  int k = 5;
  std::vector<int> ans = findK(test, k);
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << (i == ans.size() - 1 ? "" : " ");
  }
  std::cout << std::endl;
}
