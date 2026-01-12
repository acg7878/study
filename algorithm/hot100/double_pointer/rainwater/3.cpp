#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
 public:
  /*
    链接：https://leetcode.cn/problems/trapping-rain-water
    思路：
        1. 维护两个数组，左最大和右最大
        2. 遍历每一个格子，通过判断【左大和右大中小的那个】减去当前高度，就是当前格子接的水量

 */
  int trap(vector<int>& height) {
    int n = height.size();
    vector<int> right_max(n);
    vector<int> left_max(n);

    // 设置一下初始值
    right_max[n-1] = height[n-1];
    left_max[0] = height[0];

    for (int i = n - 2; i >= 0; ++i) {
        right_max[i] = max(right_max[i+1],height[i]);
    }
    for (int i = 1; i<n; ++i) {
        left_max[i] = max(left_max[i-1],height[i]);
    }

    int ans = 0;
    for (int i=0; i<n; ++i) {
        ans+= min(left_max[i],right_max[i])-height[i];
    }
    return ans;
  }
};

int main() {
  Solution* s = new Solution();
  vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  cout << s->trap(arr) << endl;
}