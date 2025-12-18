#include <string>
#include <vector>

using namespace std;

class Solution {
 private:
  const vector<string> KEYBOARD = {"",    "",    "abc",  "def", "ghi",
                                   "jkl", "mno", "pqrs", "tuv", "wxyz"};

  vector<string> result;
  string path;

  void backtracking(const string& digits, int index) {
    if (path.size() == digits.size()) {
      result.emplace_back(path);
      return;
    }

    int digit = digits[index] - '0';
    const string& letters = KEYBOARD[digit];
    for (char c : letters) {
      path.push_back(c);
      backtracking(digits, index + 1);
      path.pop_back();
    }
  }

 public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) {
      return result;
    }

    backtracking(digits, 0);
    return result;
  }
};
