/*
Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.
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
    int getMinimumDifference(TreeNode* root) {
        int minDiff = INT_MAX;
        int val = -1;
        inorderTraverse(root, val, minDiff);
        return minDiff;
    }
    
    void inorderTraverse(TreeNode *curNode, int &val, int &minDiff) {
        if (curNode->left) inorderTraverse(curNode->left, val, minDiff);
        if (val >= 0) minDiff = min(minDiff, curNode->val - val);
        val = curNode->val;
        if (curNode->right) inorderTraverse(curNode->right, val, minDiff);
    }
};
