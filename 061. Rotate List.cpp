/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/

/*
Analysis: The idea is quite simple: traverse the list until the last node (and thus we know the length of the list). Now link the last node to the first node and now we get a circular list. Keep walking len - k%len nodes and then break the list there. The result is a rotated list.
*/
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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !k) return head;
        int len = 1;
        ListNode *p = head;
        while (p->next) {
            len++;
            p = p->next;
        }
        p->next = head;
        for (int i = 0; i < len-k%len; i++) p = p->next;
        ListNode *newHead = p->next;
        p->next = NULL;
        return newHead;
    }
};
