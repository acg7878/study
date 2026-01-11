#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> path;
  vector<bool> on_path;
  vector<vector<int>> ans;
  vector<vector<int>> permute(vector<int>& nums) {
    path.clear();
    ans.clear();
    on_path.resize(nums.size(), false);
    dfs(nums);
    return ans;
  }

  void dfs(const vector<int>& nums) {
    if (path.size() == nums.size()) {
      ans.push_back(path);
      return;
    }
    for (int i = 0; i < nums.size(); ++i) {
      if (!on_path[i]) {
        path.push_back(nums[i]);
        on_path[i] = true;
        dfs(nums);
        on_path[i] = false;
        path.pop_back();
      }
    }
  }
};

int main() {
  Solution s;
  vector<int> exp = {1, 2, 3};
  vector<vector<int>> ans = s.permute(exp);
  for (auto nums : ans) {
    for (auto num : nums) {
      cout << num << " ";
    }
    cout << endl;
  }
}