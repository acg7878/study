#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    auto cmp = [](vector<int>& a, vector<int>& b) {
      return *a.begin() < *b.begin();
    };
    sort(intervals.begin(), intervals.end(), cmp);
    vector<vector<int>> ans;
    for (const auto& arr : intervals) {
      if (!ans.empty() && arr[0] <= ans.back()[1]) {
        ans.back()[1] = max(ans.back()[1], arr[1]);
      } else {
        ans.emplace_back(arr);
      }
    }
    return ans;
  }
};