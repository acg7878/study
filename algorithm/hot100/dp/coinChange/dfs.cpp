#include <vector>
#include <climits>

using namespace std;

class Solution {
    // 记忆化数组：memo[i] 存储凑齐金额 i 所需的最少硬币数
    // 0 表示未计算，-1 表示无法凑齐，>0 表示结果
    vector<int> memo;

public:
    int coinChange(vector<int>& coins, int amount) {
        // 初始化 memo，大小为 amount + 1
        memo.resize(amount + 1, 0);
        return dfs(coins, amount);
    }

    // 定义：凑齐 amount 金额所需的最少硬币数
    int dfs(const vector<int>& coins, int amount) {
        // 1. 递归终止条件
        if (amount < 0) return -1;
        if (amount == 0) return 0;
        
        // 2. 查表：如果已经计算过，直接返回
        if (memo[amount] != 0) {
            return memo[amount];
        }

        // 3. 递归逻辑
        int minCount = INT_MAX;
        for (int coin : coins) {
            int res = dfs(coins, amount - coin);
            
            // 如果子问题有解 (res != -1)，且更优，则更新
            if (res >= 0 && res < minCount) {
                minCount = res + 1;
            }
        }

        // 4. 存表并返回
        // 如果 minCount 还是 INT_MAX，说明无解，记为 -1
        memo[amount] = (minCount == INT_MAX) ? -1 : minCount;
        return memo[amount];
    }
};