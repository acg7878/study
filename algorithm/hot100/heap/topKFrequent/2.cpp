#include <functional>
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

    // 注意greater，他是用first来排序的
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    for (auto& [num, count] : um) {
      if (pq.size() < k) {
        pq.emplace(count, num);
      } else {
        if (pq.top().first < count) {
          pq.pop();
          pq.emplace(count, num);
        }
      }
    }
    vector<int> ans;
    while (!pq.empty()) {
      ans.push_back(pq.top().second);
      pq.pop();
    }
    return ans;
  }
};