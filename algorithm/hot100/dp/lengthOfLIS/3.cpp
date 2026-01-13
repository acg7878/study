#include <algorithm>
#include <vector>
using namespace std;

/*

    链接：https://leetcode.cn/problems/longest-increasing-subsequence/
    思路：
        1. dp的思路
        2. 两层遍历，第一次0-size,第二层0-i;
        3. 状态转移公式：dp[i] = max(dp[i],dp[j]+1);
            ⬆️当nums[j] < nums[i]时，通过判断



*/

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    int ans = 0;
    vector<int> dp(nums.size(), 1);
    for (int i = 0; i < nums.size(); i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
      ans = max(ans, dp[i]);
    }
    return ans;
  }
};
