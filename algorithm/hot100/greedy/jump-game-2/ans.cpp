#include <vector>
#include <algorithm>
using namespace std;

/* 
    链接：https://leetcode.cn/problems/jump-game-ii
    思路：
        1. 贪心算法
        2. 维护当前覆盖最远距离 curDistance 和 下一步覆盖最远距离 nextDistance
        3. 当遍历到 curDistance 时，更新 ans++ 并将 curDistance 更新为 nextDistance
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        
        int curDistance = 0;  // 当前覆盖的最远距离下标
        int nextDistance = 0; // 下一步覆盖的最远距离下标
        int ans = 0;          // 记录走的最大步数
        
        for (int i = 0; i < nums.size(); i++) {
            // 在当前覆盖范围内，寻找下一步能跳到的最远位置
            nextDistance = max(nextDistance, i + nums[i]);
            
            // 遇到当前覆盖的最远距离下标时
            if (i == curDistance) {
                ans++; // 需要再跳一步
                curDistance = nextDistance; // 更新当前覆盖的最远距离下标
                
                // 如果当前覆盖最远距离下标已经到达终点，结束
                if (curDistance >= nums.size() - 1) break;
            }
        }
        return ans;
    }
};