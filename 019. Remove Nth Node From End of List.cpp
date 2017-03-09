/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/

// Time: O(n), Space: O(1). 1 Pass.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) return head;
        int count = 0;
        ListNode *back = head, *front = head;
        while (count < n) {
            front = front->next;
            count++;
        }
        if (front == NULL) return head->next;
        while (front->next) {
            back = back->next;
            front = front->next;
        }
        // delete back->next;
        ListNode *nextNode = back->next->next;
        back->next = nextNode;
        return head;
    }
};
