#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
 public:
  int trap(vector<int>& height) {
    int size = height.size();
    vector<int> left_max(size);
    vector<int> right_max(size);

    left_max[0] = height[0];
    right_max[size - 1] = height[size - 1];

    for (int i = size - 2; i >= 0; --i) {
      right_max[i] = max(right_max[i + 1], height[i]);
    }
    for (int i = 1; i < size; ++i) {
      left_max[i] = max(left_max[i - 1], height[i]);
    }

    int ans = 0;
    for (int i = 0; i < size; ++i) {
      ans += min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
  }
};

int main() {
  Solution* s = new Solution();
  vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  cout << s->trap(arr) << endl;
}