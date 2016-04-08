/*
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
*/

/* Solution #1:
Time: O(n)
Space: O(n)
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
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL) return true;
        stack<int> firstHalf;
        ListNode *fast = head, *slow = head;
        
        while (fast != NULL && fast->next != NULL) {
            firstHalf.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if (fast != NULL) { // odd number of nodes in the list
            slow = slow->next;
        }
        // now slow points to the beginning of the second half
        while (slow != NULL) {
            if (firstHalf.top() != slow->val) return false;
            firstHalf.pop();
            slow = slow->next;
        }
        return true;
    }
};


/* Solution #2:
Time: O(n)
Space: O(1)
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
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL) return true;
        ListNode *fast = head, *slow = head;
        ListNode *secondHalf;
        ListNode *slowPrev = head;
        ListNode *midNode = NULL;
        bool result = true;
        
        while (fast != NULL && fast->next != NULL) {
            slowPrev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
            
        if (fast != NULL) { //there are odd number of nodes in the list
            midNode = slow;
            slow = slow->next;
        }
        secondHalf = slow;
        slowPrev->next = NULL; // null terminate the first half
        secondHalf = reverseList(secondHalf);
        result = compareList(head, secondHalf);
            
        // reverse secondHalf back
        secondHalf = reverseList(secondHalf);
        if (midNode != NULL) {
            slowPrev->next = midNode;
            midNode->next = secondHalf;
        } else {
            slowPrev->next = secondHalf;
        }
        return result;
    }
    
    ListNode* reverseList(ListNode* head) {
        if (head == NULL) return head;
        ListNode *tmpNode, *prevNode;
        prevNode = NULL;
        while (head != NULL) {
            tmpNode = head->next;
            head->next = prevNode;
            prevNode = head;
            head = tmpNode;
        }
        return prevNode;
    }
    
    bool compareList(ListNode *l1, ListNode *l2) {
        ListNode *p = l1, *q = l2;
        while (p != NULL && q != NULL) {
            if (p->val != q->val) return false;
            p = p->next; 
            q = q->next;
        }
        return p == NULL && q == NULL;
    }
};
