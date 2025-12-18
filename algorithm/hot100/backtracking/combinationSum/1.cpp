#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<int>> ans;
  vector<int> path;
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    backtracking(candidates, 0, target);
    return ans;
  }

 private:
  void backtracking(const vector<int>& candidates, int start, int target) {
    if (target == 0) {
      ans.push_back(path);
      return;
    }

    for (int i = start; i < (int)candidates.size(); ++i) {
      // 剪枝
      if (target - candidates[i] < 0) {
        break;
      }
      path.push_back(candidates[i]);
      // 传入i，每一个数字可以重复被选择
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