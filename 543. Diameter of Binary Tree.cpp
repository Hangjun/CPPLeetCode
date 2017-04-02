/*
Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.
*/

/*
Analysis: The diameter of any node is given by its left substree's depth + its right substree's depth. Therefore a DFS approach is very straightforward.
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
    int res = 0;
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return res;
    }
    
    int dfs(TreeNode *curNode) {
        if (!curNode) return 0;
        int leftDepth = dfs(curNode->left);
        int rightDepth = dfs(curNode->right);
        res = max(res, leftDepth + rightDepth);
        return 1 + max(leftDepth, rightDepth);
    }
};
