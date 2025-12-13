#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hashtable;  // value，index
    for (int i = 0; i < nums.size(); ++i) {
      int need = target - nums[i];
      if (hashtable.find(need) != hashtable.end()) {
        return {hashtable.find(need)->second, i};
      }
      hashtable[nums[i]] = i;
    }
    return {};
  }
};