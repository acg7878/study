#include <climits>  // 为了使用 INT_MAX
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    int s_size = s.size();
    int count = t.size();

    // 记录 t 中每个字符需要的数量
    unordered_map<char, int> um;
    for (char c : t) {
      um[c]++;
    }

    int left = 0, right = 0;
    int min_len = INT_MAX;
    int start_index = 0;

    while (right < s_size) {
      // 消费一个字符：如果是 t 中需要的字符，count 减 1
      if (um[s[right]] > 0) {
        count--;
      }
      // 无论是否是 t 中的字符，窗口内的该字符计数都减 1
      // (对于 t 中没有的字符，计数会变成负数)
      um[s[right]]--;

      // 当 count == 0 时，说明窗口已包含 t 中所有字符，尝试收缩
      while (count == 0) {
        // 更新最小窗口
        if (right - left + 1 < min_len) {
          min_len = right - left + 1;
          start_index = left;
        }

        // 移动 left 指针，尝试缩小窗口
        // s[left] 即将移出窗口，计数加 1
        um[s[left]]++;

        // 如果 s[left] 是 t 中必需的字符（计数变回 > 0），
        // 说明移出后窗口不再满足条件，count 需要加 1
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