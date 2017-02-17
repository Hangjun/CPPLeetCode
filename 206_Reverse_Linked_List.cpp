/*
Reverse a singly linked list.

click to show more hints.
Hint:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

// Iterative solution.
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
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        ListNode *prev = NULL;
        ListNode *tmp;
        
        while (head != NULL) {
            tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        
        return prev;
    }
};

// Recursive solution.
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
    ListNode* reverseList(ListNode* head) {
        return reverseListRecur(head, NULL);
    }
    
    ListNode *reverseListRecur(ListNode *&head, ListNode *newHead) {
        if (!head) return newHead;
        ListNode *nextNode = head->next;
        head->next = newHead;
        return reverseListRecur(nextNode, head);
    }
};
