#include <iostream>
#include <vector>
class Solution {
 public:
  std::vector<int> path;
  std::vector<int> used;
  std::vector<std::vector<int>> ans;
  std::vector<std::vector<int>> permutation(std::vector<int>& nums) {
    used.assign(nums.size(), 0);
    dfs(nums);
    return ans;
  }

  void dfs(const std::vector<int>& nums) {
    if (path.size() == nums.size()) {
      ans.push_back(path);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i]) {
        continue;
      }
      path.push_back(nums[i]);
      used[i] = 1;
      dfs(nums);
      path.pop_back();
      used[i] = 0;
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