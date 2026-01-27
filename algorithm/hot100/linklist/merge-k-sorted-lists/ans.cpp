// 分治思路

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
    return divide(lists, 0, lists.size() - 1);
  }

 private:
  // 分治：将 lists[left..right] 区间的链表合并
  ListNode* divide(vector<ListNode*>& lists, int left, int right) {
    if (left > right) return nullptr;
    if (left == right) return lists[left];

    int mid = left + (right - left) / 2;

    // 递归合并左右两部分
    ListNode* leftHalf = divide(lists, left, mid);
    ListNode* rightHalf = divide(lists, mid + 1, right);

    // 合并两个有序链表
    return mergeTwoLists(leftHalf, rightHalf);
  }

  // 合并两个有序链表
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (l1 && l2) {
      if (l1->val <= l2->val) {
        tail->next = l1;
        l1 = l1->next;
      } else {
        tail->next = l2;
        l2 = l2->next;
      }
      tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;
    return dummy.next;
  }
};