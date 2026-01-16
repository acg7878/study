#include <iostream>
#include <vector>
class Solution {
 public:
  std::vector<int> path;
  std::vector<bool> on_path;
  std::vector<std::vector<int>> ans;
  std::vector<std::vector<int>> permutation(std::vector<int>& nums) {
    on_path.resize(nums.size(), false);
    dfs(nums);
    return ans;
  }

  void dfs(const std::vector<int>& nums) {
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
  std::vector<int> arr = {1, 2, 3, 4};
  std::vector<std::vector<int>> ans = s.permutation(arr);

  for (auto nums : ans) {
    for (auto num : nums) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}