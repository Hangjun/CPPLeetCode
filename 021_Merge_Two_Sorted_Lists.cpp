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
        ListNode *dummyNode = new ListNode(-1);
        ListNode *head = dummyNode;
        
        while (l1 || l2) {
            if (l1 && l2) {
                if (l1->val < l2->val) {
                    head->next = new ListNode(l1->val);
                    l1 = l1->next;
                } else {
                    head->next = new ListNode(l2->val);
                    l2 = l2->next;
                }
            } else if (l1) {
                head->next = new ListNode(l1->val);
                l1 = l1->next;
            } else if (l2) {
                head->next = new ListNode(l2->val);
                l2 = l2->next;
            }
            head = head->next;
        }
        
        return dummyNode->next;
    }
};

/*
This problem explicitly requires the merged list to be a newly created list. However, if we can modify the lists in-place, here is its implementation:
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
        ListNode *dummyNode = new ListNode(-1);
        ListNode *prevNode = dummyNode;
        prevNode->next = l1;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                l1 = l1->next;
            } else {
                ListNode *tmp = l2->next;
                prevNode->next = l2;
                l2->next = l1;
                l2 = tmp;
            }
            prevNode = prevNode->next;
        }
        
        if (l2) prevNode->next = l2;
        return dummyNode->next;
    }
};
