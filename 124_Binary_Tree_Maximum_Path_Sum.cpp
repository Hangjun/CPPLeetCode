/*
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.
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
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        findMaxPathSum(root, maxSum);
        return maxSum;
    }
    
    int findMaxPathSum(TreeNode *curNode, int &maxSum) {
        if (curNode == NULL) return 0;
        int pathSum1Left = 0, pathSum1Right = 0;
        
        if (curNode->left) pathSum1Left = max(findMaxPathSum(curNode->left, maxSum), 0);
        if (curNode->right) pathSum1Right = max(findMaxPathSum(curNode->right, maxSum), 0);
        
        int pathSum1CurNode = max(max(pathSum1Left, 0), max(pathSum1Right, 0)) + curNode->val;
        int pathSum2CurNode = max(pathSum1Left, 0) + curNode->val + max(pathSum1Right, 0);
        
        maxSum = max(maxSum, max(pathSum1CurNode, pathSum2CurNode));
        
        return pathSum1CurNode;
    }
};
