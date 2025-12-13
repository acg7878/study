#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    // 有序才能使用双指针，但是排序会打乱坐标，所以用pair记录一下
    vector<pair<int, int>> arr;
    for (int i = 0; i < nums.size(); ++i) {
      arr.push_back({nums[i], i});
    }
    sort(arr.begin(), arr.end());
    int i = 0, j = arr.size() - 1;

    while (i < j) {
      int sum = arr[i].first + arr[j].first;
      if (sum == target) {
        return {arr[i].second, arr[j].second};
      } else if (sum < target) {
        i++;
      } else {
        j--;
      }
    }
    return {};
  }
};