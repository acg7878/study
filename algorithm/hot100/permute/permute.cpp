#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> on_path(n, false);

    function<void()> dfs = [&]() {
      if (path.size() == n) {
        ans.push_back(path);
        return;
      }

      for (int i = 0; i < n; ++i) {
        if (!on_path[i]) {
          on_path[i] = true;
          path.push_back(nums[i]);
          dfs();
          on_path[i] = false;
          path.pop_back();
        }
      }
    };

    dfs();
    return ans;
  }
};

int main() {
  Solution s;
  vector<int> exp = {1, 2, 3, 4};
  vector<vector<int>> ans = s.permute(exp);
  for (auto nums : ans) {
    for (auto num : nums) {
      cout << num << " ";
    }
    cout << endl;
  }
}