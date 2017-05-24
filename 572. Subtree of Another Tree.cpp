/*
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
*/

/*
Analysis: A typical solution is to use recursion and check if a subtree of s is the same binary tree as t.
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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == NULL) return false; // Caution: need to add this check!
        return isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    
    bool isSameTree(TreeNode *s, TreeNode *t) {
        if (s == NULL) return t == NULL;
        if (t == NULL) return s == NULL;
        if (s->val != t->val) return false;
        return isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
    }
};

/* 
Another solution is to compute the preorder (or any other order for that matter) of both s and t and check if the preorder sequence of t is a subsequence of that of s. KMP algorithm computes it in O(m+n) time, where m = |s| and n = |t|.
*/
