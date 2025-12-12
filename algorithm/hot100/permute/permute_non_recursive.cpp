#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans;
    if (n == 0)
      return ans;

    // 定义栈中存储的状态：
    // 第一个元素：当前要填充的位置 i
    // 第二个元素：当前的 path 数组
    // 第三个元素：当前的 on_path 标记数组
    stack<tuple<int, vector<int>, vector<int>>> st;

    // 初始状态：i=0，空path，全未选中的on_path
    st.emplace(0, vector<int>(n), vector<int>(n, 0));

    while (!st.empty()) {
      // 弹出栈顶状态（模拟递归调用返回）
      auto [i, path, on_path] = st.top();
      st.pop();

      // 递归终止条件：已构建完完整排列
      if (i == n) {
        ans.emplace_back(path);
        continue;
      }

      // 枚举所有未被选中的元素（注意：栈是后进先出，所以倒序枚举，保证结果顺序和递归版一致）
      for (int j = n - 1; j >= 0; j--) {
        if (!on_path[j]) {
          // 复制当前状态，修改后压入栈（模拟递归调用）
          vector<int> new_path = path;
          vector<int> new_on_path = on_path;
          new_path[i] = nums[j];                     // 填充第i位
          new_on_path[j] = 1;                        // 标记为已选中
          st.emplace(i + 1, new_path, new_on_path);  // 压入下一层状态
        }
      }
    }

    return ans;
  }
};

int main() {
  Solution s;
  vector<int> exp = {1, 2, 3,4};
  vector<vector<int>> ans = s.permute(exp);
  for (auto nums : ans) {
    for (auto num : nums) {
      cout << num << " ";
    }
    cout << endl;
  }
}