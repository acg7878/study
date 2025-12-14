#include <deque>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans(n - k + 1);
    deque<int> q;

    for (int i = 0; i < n; ++i) {
      // 右边入
      while (!q.empty() && nums[q.back()] <= nums[i]) {
        q.pop_back();  // 维护队列单调性
      }
      q.push_back(i);  // 注意保存的是下标，这样下面可以判断队首是否离开窗口

      // 左边出
      int left = i - k + 1;
      if (q.front() < left) {
        q.pop_front();
      }

      // 在窗口左端点处记录答案
      if (left >= 0) {
        // 由于队首到队尾单调递减，所以窗口最大值就在队首
        ans[left] = nums[q.front()];
      }
    }
    return ans;
  }
};