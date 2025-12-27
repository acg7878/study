#include <climits>
#include <string>
#include <unordered_map>
using namespace std;

// 思路：哈希表记录一下 t字符串 没给字符出现的次数
// 用滑动窗口来尝试覆盖，right++进行窗口扩张
// 覆盖后尝试收缩（left--）


class Solution {
 public:
  string minWindow(string s, string t) {
    int right = 0;
    int left = 0;
    int s_size = s.size();
    int count = t.size();  // 归0代表窗口覆盖了

    int min_size = INT_MAX;
    int start_index = -1;

    unordered_map<char, int> um;  // 字符，次数
    for (char c : t) {
      um[c]++;
    }

    while (right < s_size) {
      // 先消费
      if (um[s[right]] > 0) {
        count--;
      }
      um[s[right]]--;

      while (count == 0) {
        // 符合最小标准，记录一下
        if (right - left + 1 < min_size) {
          min_size = right - left + 1;
          start_index = left;
        }

        // 尝试移动,增加被移出的那个字符的次数
        um[s[left]]++;
        // 被移出的是我们需要的字符，增加count
        if (um[s[left]] > 0) {
          count++;
        }
        left++;
      }
      right++;
    }
    return min_size == INT_MAX ? "" : s.substr(start_index, min_size);
  }
};