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

/*
  链接：https://leetcode.cn/problems/palindrome-linked-list/description/
  思路
    1. 找中点，翻转另一半
    2. 看看这两个链表相同否
*/

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  bool isPalindrome(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return isSame(head, reverseList(slow));
  }

  bool isSame(ListNode* node1,ListNode* node2) {
    while (node1 && node2) {
      if (node1->val != node2->val) {
        return  false;
      }
      node1 = node1->next;
      node2 = node2->next;
    }
    return true;
  }
  ListNode* reverseList(ListNode* head) {
    ListNode* pre = nullptr;
    ListNode* cur = head;
    while (cur) {
      ListNode* next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return pre;
  }
};