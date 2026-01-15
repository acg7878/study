#include <vector>
using namespace std;

#include <algorithm>

class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    // dp[i] 表示凑成金额 i 所需的最少硬币数
    // 初始化为 amount + 1，表示一个不可能达到的最大值（因为硬币面额最小为1，最多也只需要 amount 个）
    vector<int> dp(amount + 1, amount + 1);
    
    // 凑成金额 0 不需要任何硬币
    dp[0] = 0;

    // 遍历所有金额，从 1 到 amount
    for (int i = 1; i <= amount; ++i) {
      // 遍历每一种硬币
      for (int coin : coins) {
        // 如果当前金额 i 足以容纳这枚硬币
        if (i >= coin) {
          // 状态转移：尝试用这枚硬币，看看是否能减少总数
          dp[i] = min(dp[i], dp[i - coin] + 1);
        }
      }
    }

    // 如果 dp[amount] 仍然是初始值，说明无法凑成，返回 -1
    return dp[amount] > amount ? -1 : dp[amount];
  }
};