/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1. 
*/


// A straightfoward solution is to compute the depth of each node in the tree, and test balancedness at each node:
// Time O(n^2).
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
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        int diff = abs(maxDepth(root->left) - maxDepth(root->right));
        if (diff > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
    
    int maxDepth(TreeNode *root) {
        if (!root) return 0;
        if (root->left == NULL && root->right == NULL) return 1;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};


/* Analysis:
There are many redundant computations above, and maxDepth is called at every node, therefore resulting a O(n^2) time. Instead of approaching this top-down, we can take a dynamic programming approach and go bottom-up.

The idea is simple: at each node, we do two things: 1) compute its height via DFS; 2) test balancedness and pass the information upstream. This way the height computation is done precisely once per node.
*/

// DFS solution. Time O(n):
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
    bool isBalanced(TreeNode* root) {
        return heightDFS(root) != -1;
    }
    
    // compute the height of each node via DFS, and determine whether a node is balanced as soon as the DFS heights of its 
    // children are returned
    int heightDFS(TreeNode *curNode) {
        if (!curNode) return 0;
        
        int leftHeight = heightDFS(curNode->left);
        if (leftHeight == -1) return -1; // pass the unblanaced information upstream via the return value of -1
        
        int rightHeight = heightDFS(curNode->right);
        if (rightHeight == -1) return -1; // pass the unblanaced information upstream via the return value of -1
        
        // now that both left child and right child are both balanced, determine whether curNode is balanced
        if (abs(leftHeight - rightHeight) > 1) return -1;
        
        return 1 + max(leftHeight, rightHeight);
    }
};
