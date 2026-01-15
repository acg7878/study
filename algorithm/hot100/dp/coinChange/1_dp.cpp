#include <vector>
using namespace std;

#include <algorithm>

class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
      for (int coin : coins) {
        if (i >= coin) {
            // 使用这枚硬币是否更省次数？
            // 是的话就将状态数组中 凑i-coin需要的硬币数 +1
          dp[i] = min(dp[i], dp[i - coin] + 1);
        }
      }
    }
    return dp[amount]==amount+1? -1 : dp[amount];
  }
};