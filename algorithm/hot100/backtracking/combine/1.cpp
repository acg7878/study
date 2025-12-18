// https://leetcode.cn/problems/combinations
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<int>> ans;
  vector<int> path;
  vector<vector<int>> combine(int n, int k) {
    backtracking(1, n, k);
    return ans;
  }

  void backtracking(int index, int n, int k) {
    if (path.size() == k) {
      ans.push_back(path);
      return;
    }

    for (int i = index; i <= n; ++i) {
      path.push_back(i);
      backtracking(i + 1, n, k);
      path.pop_back();
    }
  }
};

int main() {
  Solution s;
  vector<vector<int>> ans = s.combine(4, 2);
  for (auto nums : ans) {
    for (auto num : nums) {
      cout << num << " ";
    }
    cout << "\n";
  }
}