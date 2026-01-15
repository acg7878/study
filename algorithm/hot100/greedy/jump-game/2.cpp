#include <algorithm>
#include <vector>
using namespace std;

/*
    链接：https://leetcode.cn/problems/jump-game
    思路：
        遍历，并维护一个最大可到达格子索引。

*/

class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int x = 0;
    for (int i = 0; i <= x; ++i) {
      x = max(i + nums[i], x);
      if (x >= nums.size() - 1) {
        return true;
      }
    }
    return false;
  }
};