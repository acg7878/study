#include <algorithm>
#include <vector>
using namespace std;

/*
    链接：https://leetcode.cn/problems/rotate-array/description/
    思路：
    1. 整个数组反转
    2. 前k个区间和其他区间，都反转一下


*/


class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin()+k);
    reverse(nums.begin()+k, nums.end());
  }
};