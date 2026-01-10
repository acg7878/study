#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    int ans = 0;
    // 单个字符就是一个子序列
    vector<int> dp(nums.size(), 1);
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[j] < nums[i]) {
            dp[i] = max(dp[i],dp[j]+1);
        }
      }
      ans = max(ans,dp[i]);
    }
    return ans;
  }
};
