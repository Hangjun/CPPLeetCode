/*
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/

/* Analysis:
It is easy to see that this is a DFS problem. The key is to compute the number of legitimate paths eminating from EVERY node in the tree.
*/

// DFS solution:
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
    int pathSum(TreeNode* root, int sum) {
        if (!root) return 0;
        /* 
         * the recursion on pathSum(root->left, sum) and pathSum(root->right, sum) is to compute number of 
         * legitimate paths eminating from EVERY node in the tree.
         */
        return pathSumCountDFS(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
    
    int pathSumCountDFS(TreeNode *curNode, int target) {
        if (!curNode) return 0;
        target -= curNode->val;
        return (target == 0) + pathSumCountDFS(curNode->left, target) + pathSumCountDFS(curNode->right, target);
    }
};
