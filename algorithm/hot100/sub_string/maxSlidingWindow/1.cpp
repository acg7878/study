#include <deque>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;  // 维护一个单调队列，存的是下标
    vector<int> ans(n - k + 1);

    for (int i = 0; i < n; ++i) {
      // 右边入
      while (!q.empty() && nums[q.back()] <= nums[i]) {
        q.pop_back();
      }
      q.push_back(i);

      // 左边出
      int left = i - k + 1;
      if (q.front() < left) {
        // 队头已经不在滑动窗口内了，需要踢出
        // 所以我们的队列才存坐标
        q.pop_front();
      }

      // 记录答案
      if (left >= 0) {
        ans[left] = nums[q.front()];
      }
    }
    return ans;
  }
};