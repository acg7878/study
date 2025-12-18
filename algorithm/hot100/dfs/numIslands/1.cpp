#include <vector>
using namespace std;

class Solution {
 public:
  int m, n;  // 地图范围
  int numIslands(vector<vector<char>>& grid) {
    m = grid.size();
    n = grid[0].size();

    int ans = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '1') {
          dfs(grid, i, j);
          ans++;
        }
      }
    }
    return ans;
  }

  // i,j:坐标
  void dfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || i >= m || j < 0 || j > n || grid[i][j] != '1') {
      return;
    }
    grid[i][j] = '0';
    dfs(grid, i - 1, j);  // 上
    dfs(grid, i + 1, j);  // 下
    dfs(grid, i, j - 1);  // 左
    dfs(grid, i, j + 1);  // 右
  }
};