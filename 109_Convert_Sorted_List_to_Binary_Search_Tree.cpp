/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/

// Solution #1: Recursion. Time = O(nlogn), Space = O(1).
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == NULL) return NULL;
        ListNode *fast, *slow, *mid;
        fast = slow = mid = head;
        
        while (fast && fast->next) {
            mid = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        mid->next = NULL;
        mid = slow;
        slow = slow->next;
        TreeNode *root = new TreeNode(mid->val);
        if (head != mid)
            root->left = sortedListToBST(head);
        if (slow != NULL)
            root->right = sortedListToBST(slow);
            
        return root;
    }
};

// Solution #2: Time = O(n), Space = O(1)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        /* Linear Time Algorithm: "DFS on a linked list" */
        /* head == NULL check is only a time saver: not 
            necessary for correctness
        */
        if (head == NULL) return NULL; 
        ListNode *curNode = head;
        int listLen = 0;
        while (curNode) {
            listLen++;
            curNode = curNode->next;
        }
        return sortedListToBSTRecur(head, 0, listLen-1);
    }
    
    TreeNode *sortedListToBSTRecur(ListNode *&head, int start, int end) {
        if (start > end) return NULL;
        int mid = start + (end - start)/2;
        TreeNode *leftChild = sortedListToBSTRecur(head, start, mid-1);
        TreeNode *root = new TreeNode(head->val);
        head = head->next;
        TreeNode *rightChild = sortedListToBSTRecur(head, mid+1, end);
        root->left = leftChild;
        root->right = rightChild;
        return root;
    }
};
