// https://leetcode.cn/problems/generate-parentheses?envType=study-plan-v2&envId=top-100-liked
#include <string>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<string> ans;
    string path;

    auto dfs = [&](this auto&& dfs, int left, int right) -> void {
      if (left == n && right == n) {
        ans.push_back(path);
        return;
      }

      if (left < n) {
        path.push_back('(');
        dfs(left + 1, right);
        path.pop_back();
      }

      if (right < left) {
        path.push_back(')');
        dfs(left, right + 1);
        path.pop_back();
      }
    };

    dfs(0, 0);
    return ans;
  }
};
