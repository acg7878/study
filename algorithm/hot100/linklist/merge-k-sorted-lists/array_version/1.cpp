#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

struct Node {
  int val;
  int index;  // 内部序号
  int vec_index;

  Node(int v, int i, int vi) : val(v), index(i), vec_index(vi) {}

  bool operator>(const Node& other) const {
      return val > other.val;
  }
};

class Solution {
 public:
  vector<int> mergeKArrays(vector<vector<int>>& arrays) {
    // 使用 greater<> 需要 Node 类重载 > 运算符
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int cnt = 0;
    for (const auto& array : arrays) {
      if (!array.empty()) { // 必须判空，防止空数组导致越界
          pq.push(Node{array[0], 0, cnt});
      }
      cnt++;
    }
    vector<int> ans;
    while (!pq.empty()) {
      auto node = pq.top();
      pq.pop();
      ans.push_back(node.val);
      if (static_cast<size_t>(node.index + 1) < arrays[node.vec_index].size()) {
        pq.emplace(arrays[node.vec_index][node.index + 1], node.index + 1,
                   node.vec_index);
      }
    }
    return ans;
  }
};


int main() {
    Solution sol;
    
    // 测试用例 1: 正常情况
    vector<vector<int>> arrays1 = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    vector<int> res1 = sol.mergeKArrays(arrays1);
    
    cout << "Test Case 1 Output: ";
    for (int num : res1) cout << num << " ";
    cout << endl;
    
    vector<int> expected1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(res1 == expected1);
    cout << "Test Case 1 Passed!" << endl;

    // 测试用例 2: 包含空数组
    vector<vector<int>> arrays2 = {
        {},
        {1, 3, 5},
        {2, 4}
    };
    vector<int> res2 = sol.mergeKArrays(arrays2);
    
    cout << "Test Case 2 Output: ";
    for (int num : res2) cout << num << " ";
    cout << endl;
    
    vector<int> expected2 = {1, 2, 3, 4, 5};
    assert(res2 == expected2);
    cout << "Test Case 2 Passed!" << endl;
    
    return 0;
}