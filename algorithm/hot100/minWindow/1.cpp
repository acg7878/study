#include <climits>  // 为了使用 INT_MAX
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    int left = 0, right = 0;  // 滑动窗口
    int s_size = s.size();
    int count = t.size();

    int min_size = INT_MAX;
    int start_index = -1;
    unordered_map<char, int> um;  // 哈希表记录每个字符个数
    for (char c : t) {
      um[c]++;
    }
    while (right < s_size) {
      if (um[s[right]] > 0) {
        count--;
      }

      // 不管需不需要都消费一下，消费的是不需要的也无所谓
      um[s[right]]--;

      // 满足要求，触发收缩找到最适合的一个窗口
      while (count == 0) {
        if (right - left + 1 < min_size) {
          start_index = left;
          min_size = right - left + 1;
        }

        // 窗口左边界收缩
        um[s[left]]++;
        // 如果收缩后，某个字符不存在了，不符合要求，就将count++跳出收缩继续滑动
        if (um[s[left]] > 0) {
          count++;
        }
        left++;
      }
      right++;  // 扩大窗口
    }
    return min_size == INT_MAX ? "" : s.substr(start_index, min_size);
  }
};