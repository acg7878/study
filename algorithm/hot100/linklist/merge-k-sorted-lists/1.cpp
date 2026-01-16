#include <queue>
#include <vector>
using namespace std;
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) {
      return a->val > b->val;
    };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq;
    for (auto list : lists) {
      if (list) {
        pq.push(list);
      }
    }

    // 需要一个dummy串起来
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    while (!pq.empty()) {
      auto node = pq.top();
      pq.pop();
      cur->next = node;
      cur = node;
      if (node->next) {
        pq.push(node->next);
      }
    }
    return dummy->next;
  }
};