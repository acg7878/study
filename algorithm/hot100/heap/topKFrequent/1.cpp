#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> um;
    for (int num : nums) {
      um[num]++;
    }

    // 小顶堆，更高的频率放后面
    auto cmp = [](pair<int, int> a, pair<int, int> b) {
      return a.second > b.second;
    };
    // pair: 值，出现次数
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(
        cmp);

    for (auto& [num, count] : um) {
      if (pq.size() < k) {
        pq.emplace(num, count);
      } else if (count > pq.top().second) {
        pq.pop();
        pq.emplace(num, count);
      }
    }

    vector<int> ans;
    while (!pq.empty()) {
      ans.emplace_back(pq.top().first);
      pq.pop();
    }
    return ans;
  }
};