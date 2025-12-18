#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<int>> ans;
  vector<int> path;
  vector<vector<int>> subsets(vector<int>& nums) {
    dfs(nums, 0);
    return ans;
  }
  void dfs(const vector<int>& nums, int index) {
    ans.push_back(path);

    for (int i = index; i < nums.size(); ++i) {
      path.push_back(nums[i]);
      dfs(nums, i + 1);
      path.pop_back();
    }
  }
};

int main() {
  Solution s;
  vector<int> sets = {1, 2, 3, 4};
  vector<vector<int>> ans = s.subsets(sets);

  for (auto nums : ans) {
    for (auto num : nums) {
        cout << num << " ";
    }
    cout << endl;
  }
}