#include <string>
using namespace std;

// https://leetcode.cn/problems/add-strings/description/

class Solution {
 public:
  string addStrings(string num1, string num2) {
      int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
      string ans;
      while (i >= 0 || j >= 0 || carry) {
        int n1 = i >= 0 ? num1[i] - '0' : 0;
        int n2 = j >= 0 ? num2[j] - '0' : 0;
        int sum = n1 + n2 + carry;
        ans.push_back('0' + sum % 10);
        carry = sum / 10;
        i--;
        j--;
      }
      reverse(ans.begin(), ans.end());
      return ans;
  }
};