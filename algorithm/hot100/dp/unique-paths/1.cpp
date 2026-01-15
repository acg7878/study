#include <vector>
using namespace std;
/*
    链接：https://leetcode.cn/problems/unique-paths/
    思路：
        1. 动态规划
        2. dp[i][j] 表示从(0,0)出发到(i,j)有多少条不同的路径
        3. 状态转移方程：dp[i][j] = dp[i-1][j] + dp[i][j-1]
        4. 初始化：第一行和第一列只能通过一直向右或一直向下到达，路径数为1
*/
class Solution {
 public:
  int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0 || j == 0) {
          dp[i][j] = 1;
        } else {
          dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
      }
    }
    return dp[m - 1][n - 1];
  }
};