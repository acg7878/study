#include <vector>
using namespace std;

class Solution {
 public:
  /*  
        链接：https://leetcode.cn/problems/number-of-islands/
        思路：
        1. dfs函数(参数：网格、ij点坐标)：上下左右，将陆地改为海
        2. 遍历网格每个单元（两层循环+一个if判断，+1技数后执行dfs）
    
    */

  int m, n;  // 地图范围
  int numIslands(vector<vector<char>>& grid) {
    m = grid.size();
    n = grid[0].size();
    int ans = 0;
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            if (grid[i][j] == '1') {
                ans++;
                dfs(grid, i, j);
            }
        }
    }
    return ans;
  }

  void dfs(vector<vector<char>>& grid, int i, int j) {
    // 跳过边界和不为陆地的
    if (i < 0 || i > m || j < 0 || j > n || grid[i][j] != '1') {
      return;
    }
    grid[i][j] = '0';
    dfs(grid, i, j + 1);  // 上
    dfs(grid, i, j - 1);
    dfs(grid, i - 1, j);
    dfs(grid, i + 1, j);
  }
};