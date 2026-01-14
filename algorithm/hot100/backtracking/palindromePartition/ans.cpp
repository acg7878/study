#include <cmath>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
private:
    void backtrack(const string& s, int start, vector<string>& current, vector<vector<string>>& result) {
        // 如果已经处理完整个字符串，保存当前分割方案
        if (start >= s.length()) {
            result.push_back(current);
            return;
        }
        
        for (int end = start; end < s.length(); end++) {
            if (isPalindrome(s, start, end)) {
                current.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, current, result);
                current.pop_back();
            }
        }
    }
    
    bool isPalindrome(const string& s, int left, int right) {
        // 双指针判断是否为回文
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

int main() {
    Solution s;
    string str = "google";
    auto x = s.partition(str);
    // print 
}