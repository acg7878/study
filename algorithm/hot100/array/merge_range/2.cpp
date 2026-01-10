#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  /*
        链接：https://leetcode.cn/problems/merge-intervals/
        思路：
        1. 先给区间排序，以每个区间的开头为排序参考
        2. 将 当前需要判断的数组开头 与 ans答案数组的末尾 进行大小判断
            如果开头 小于 末尾，说明有重合
            2.1 有重合：将ans末尾的数组与我们当前数组合并
            2.2 无重合：直接将当前数组加入ans
        3. 结束
    
    
    */
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
      return *a.begin() < *b.begin();
    };
    sort(intervals.begin(), intervals.end(), cmp);

    vector<vector<int>> ans;
    for(auto& arr : intervals) {
        if (!ans.empty() && ans.back().back() >= arr[0]) {
            ans.back().back() = max(arr.back(),ans.back().back());
        } else {
            ans.push_back(arr);
        }
    }
    return ans;
  }
};