#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  /* 
    链接：https://leetcode.cn/problems/container-with-most-water/
    思路：
      1. 双指针，指向容器的两边，初始是最左最右
      2. 计算面积，维护最大面积
      3. 移动短的一边，直到相遇
 */
  int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int max_area = 0;

    while (left <= right) {
      int area = min(height[left],height[right]) * (right - left);
      max_area = max(area,max_area);
      height[left] < height[right] ?  left++ : right--;
    }
    return max_area;
  }
};