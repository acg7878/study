#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    int cnt = 0;
    for (int num : nums) {
      if (num != 0) {
        nums[cnt] = num;
        cnt++;
      }
    }
    fill(nums.begin() + cnt, nums.end(), 0);
  }
};

void print_arr(vector<int> arr) {
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;
}

int main() {
  Solution s;
  vector<int> arr = {1, 3, 0, 3, 2, 0, 0, 23, 3};
  s.moveZeroes(arr);
  print_arr(arr);
}