#include <climits>
#include <string>
#include <unordered_map>
using namespace std;

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