#include <cmath>
#include <string>
#include <vector>
using namespace std;

/* 
    链接：https://leetcode.cn/problems/palindrome-partitioning
    思路：
        1. 回溯
        2. 停止条件：end已经大于等于str字符串长度，说明该记录这个答案了
            死记硬背吧（）
            for (int end = start; end < str.size(); end++) {
                if (isPalindrome(str, start, end)) {
                    cur.push_back(str.substr(start, end - start + 1));
                    backtrack(str, end + 1);
                 cur.pop_back();
                }
            }
*/


class Solution {
 public:
  vector<string> cur;
  vector<vector<string>> ans;

  vector<vector<string>> partition(string s) {
    backtrack(s, 0);
    return ans;
  }

  void backtrack(string str, int start) {
    if (start >= str.size()) {
      ans.push_back(cur);
      return;
    }

    for (int end = start; end < str.size(); end++) {
      if (isPalindrome(str, start, end)) {
        cur.push_back(str.substr(start, end - start + 1));
        backtrack(str, end + 1);
        cur.pop_back();
      }
    }
  }

  bool isPalindrome(const string& str, int left, int right) {
    while (left <= right) {
      if (str[left] != str[right]) {
        return false;
      }
      left++;
      right--;
    }
    return true;
  }
};