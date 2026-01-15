#include <algorithm>
#include <vector>
using namespace std;

/* 
    链接：https://leetcode.cn/problems/jump-game-ii
    思路：
        1. 贪心算法
        2. 维护当前覆盖最远距离 curDistance 和 下一步覆盖最远距离 nextDistance
        3. 当遍历到 curDistance 时，更新 ans++ 并将 curDistance 更新为 nextDistance
*/

class Solution {
 public:
  int jump(vector<int>& nums) {
    if (nums.size() == 1) {
        return 0;
    }
    int cur = 0;
    int next = 0;
    int ans = 0;
    for (int i = 0; i < nums.size(); ++i) {
      next = max(next, i + nums[i]);

      if (i == cur) {
        ans++;
        cur = next;
        if (cur >= nums.size() - 1) {
          break;
        }
      }
    }
    return ans;
  }
};