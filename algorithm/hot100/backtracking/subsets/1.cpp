#include <vector>
using namespace std;

class Solution {
 private:
  vector<int> path;
  vector<vector<int>> ans;

  void dfs(vector<int> nums, int index) {
    ans.push_back(path);
    for (int i = index; i < nums.size(); ++i) {
      path.push_back(nums[i]);
      dfs(nums, i + 1);
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    dfs(nums, 0);
    return ans;
  }
};