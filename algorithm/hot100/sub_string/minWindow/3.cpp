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
    int right = 0, left = 0;
    int s_size = s.size();
    int count = t.size();

    unordered_map<char, int> um;
    for (char c : t) {
      um[c]++;
    }

    int start_index = 0;
    int min_len = INT_MAX;

    while (right < s_size) {
      if (um[s[right]] > 0) {
        count--;
      }
      um[s[right]]--;
      while (count == 0) {
        if (right - left + 1 < min_len) {
          min_len = right - left + 1;
          start_index = left;
        }
        um[s[left]]++;
        if (um[s[left]] > 0) {
          count++;
        }
        left++;
      }
      right++;
    }
    return min_len == INT_MAX ? "" : s.substr(start_index, min_len);
  }
};