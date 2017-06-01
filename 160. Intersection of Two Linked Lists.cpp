/*
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
*/

/*
Analysis: A straightfoward solution is to adjust the starting points of two lists to be such that the lists are of equal length, and then march the two pointers ahead to find the intersection.

Time: O(m+n), Space: O(1). Need to traverse extra time to compute lengths.
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return NULL;
        
        int lenA = getLength(headA);
        int lenB = getLength(headB);
        
        while (lenA > lenB) {
            headA = headA->next;
            lenA--;
        }
        
        while (lenA < lenB) {
            headB = headB->next;
            lenB--;
        }
        
        while (headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }
        
        return headA;
    }
    
    int getLength(ListNode *listNode) {
        if (!listNode) return 0;
        int len = 0;
        while (listNode) {
            ++len;
            listNode = listNode->next;
        }
        return len;
    }
};

/*
Remark: Another sick solution is to traverse both lists and once one pointer reaches the NULL, continue traversing the other list. If the two lists intersect, they will eventually meet. If they meet at NULL, then the two lists have no intersections.

Two questions:
1. If the two lists intersect, why would the two pointers, traversed in the above fashion, meet at the intersection?
2. If the two lists do not intersect, why would the two pointers, traversed in the above fasion, end up at NULL together?

These two questions can be answered via the same length diff argument above. We leave the detailed justifications to the interested readers.

Time: O(m+n), Space: O(1). No need to traverse extra time to compute lengths.
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return NULL;
        
        ListNode *curA = headA, *curB = headB;
        while (curA != curB) {
            curA = curA ? curA->next : headB;
            curB = curB? curB->next : headA;
        }
        
        return curA;
    }
};
