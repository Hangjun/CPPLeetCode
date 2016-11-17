/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(0);
        ListNode *head = dummy;
        ListNode *p = l1;
        ListNode *q = l2;
        
        while (p && q) {
            if (p->val <= q->val) {
                head->next = new ListNode(p->val);
                p = p->next;
            } else {
                head->next = new ListNode(q->val);
                q = q->next;
            }
            head = head->next;
        }
        
        // either l1 or l2 is fully traversed
        while (p) {
            head->next = new ListNode(p->val);
            p = p->next;
            head = head->next;
        }
        
        while (q) {
            head->next = new ListNode(q->val);
            q = q->next;
            head = head->next;
        }
        
        return dummy->next;
    }
};
