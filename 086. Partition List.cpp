/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/

/*
Analysis: We manually splice the list into two linked lists, one with values less than x and the other with values greater than or eqaul to x, while we traverse the list. Then we connect the two separate lists together.

Time: O(n), Space: O(1). 1 Pass.
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
    ListNode* partition(ListNode* head, int x) {
        if (!head) return NULL;
        ListNode *dummyNode1 = new ListNode(-1);
        ListNode *dummyNode2 = new ListNode(-1);
        ListNode *p1 = dummyNode1;
        ListNode *p2 = dummyNode2;
        while (head) {
            if (head->val < x) p1 = p1->next = head;
            else p2 = p2->next = head;
            head = head->next;
        }
        p2->next = NULL;
        p1->next = dummyNode2->next;
        return dummyNode1->next;
    }
};
