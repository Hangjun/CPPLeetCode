/*
 Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/

// Depth First Search
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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        return hasPathSumDFS(root, sum);
    }
    
    bool hasPathSumDFS(TreeNode *curNode, int &target) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            return target == curNode->val;
        }
        
        // DFS step on curNode's children
        if (curNode->left) {
            target -= curNode->val;
            if (hasPathSumDFS(curNode->left, target)) return true;
            target += curNode->val;
        }
        
        if (curNode->right) {
            target -= curNode->val;
            if (hasPathSumDFS(curNode->right, target)) return true;
            target += curNode->val;
        }
        
        // the path starint from curNode does not sum up to the desired value
        return false;
    }
};

