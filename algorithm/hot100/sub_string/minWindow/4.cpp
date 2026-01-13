#include <climits>
#include <string>
#include <unordered_map>
using namespace std;

/*
    链接：https://leetcode.cn/problems/minimum-window-substring/
    思路：
        1.滑动窗口
        2.逻辑
            2.1 先消费，判断是不是在哈希表内，是的话将cnt--；
            2.2 判断cnt是否归零，是的话，对比min_len,记录start_index和长度
            2.3 尝试收缩，left开始向前
*/


class Solution {
 public:
  string minWindow(string s, string t) {
    int s_size = s.size();
    int cnt = t.size();
    unordered_map<char, int> um;  // 字符：字符数
    for (char a : t) {
      um[a]++;
    }

    int start_index = 0;
    int min_len = INT_MAX;

    int left = 0, right = 0;
    while (right < s_size) {
      // 向前移动，消费一下字符
      if (um[s[right]] > 0) {
        cnt--;
      }
      um[s[right]]--;

      // 尝试收缩
      while (cnt == 0) {
        if (right - left + 1 < min_len) {
          start_index = left;
          min_len = right - left + 1;
        }
        if (um[s[left]] == 0) {
          cnt++;
        }
        um[s[left]]++;
        left++;
      }
      right++;
    }
    return min_len == INT_MAX ? "" : s.substr(start_index, min_len);
  }
};