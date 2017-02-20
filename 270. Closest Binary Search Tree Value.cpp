/*
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.
*/

// Iterative solution: walk down the tree and update closest value.
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
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        while (root) {
            if (abs(closest - target) >= abs(root->val - target))
                closest = root->val;
                
            root = target < root->val ? root->left : root->right;
        }
        
        return closest;
    }
};

// Recursive solution.
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
    int closestValue(TreeNode* root, double target) {
        int curVal = root->val;
        TreeNode *child = target < curVal ? root->left : root->right;
        if (!child) return curVal;
        int closestRecur = closestValue(child, target);
        return abs(curVal-target) < abs(closestRecur-target) ? curVal : closestRecur;
    }
};
