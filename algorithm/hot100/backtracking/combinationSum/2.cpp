#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  /*
        链接：https://leetcode.cn/problems/combination-sum/
        思路：
            1. 排序
            2. 回溯，每个元素都可以重复选择；同时可以剪枝，已经不可能的组合直接break
            p.s.：注意start
    
    */

  vector<int> path;
  vector<vector<int>> ans;
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    backtracking(candidates, 0, target);
    return ans;
  }

  void backtracking(const vector<int>& candidates, int start, int target) {
    if (target == 0) {
      ans.push_back(path);
    }

    for (int i = start; i < candidates.size(); ++i) {
      if (target - candidates[i] < 0) {
        return;
      }
      path.push_back(candidates[i]);
      backtracking(candidates, i, target - candidates[i]);
      path.pop_back();
    }
  }
};

int main() {
  Solution s;
  vector<int> arr = {2, 3, 6, 7};
  vector<vector<int>> ans = s.combinationSum(arr, 7);
  for (auto nums : ans) {
    for (auto num : nums) {
      cout << num << " ";
    }
    cout << "\n";
  }
}