/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 思路： 递归，第一个节点处理完后，问题简化为两个链表的其余节点相加

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry = 0) {
    if (l1 == nullptr && l2 == nullptr && carry == 0) {
      return nullptr;
    }
    int s = carry;
    if (l1) {
      s += l1->val;
      l1 = l1->next;
    }

    if (l2) {
      s += l2->val;
      l2 = l2->next;
    }

    return new ListNode(s % 10, addTwoNumbers(l1, l2, s / 10));
  }
};