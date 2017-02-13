/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.
*/

/* The first idea is that, if p->right exists, the successor of p is the left most leaf of the subtree rooted at p->right. Otherwise, we binary search from root to p, and return the smallest node that's larger than p.

Time: O(h), where h is the height of the tree.
Space: O(1).

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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (!root || !p) return NULL;
        if (p->right) {
            TreeNode *nextNode = p->right;
            while (nextNode->left) nextNode = nextNode->left;
            return nextNode;
        }
        
        TreeNode *curNode = root;
        TreeNode *candidate = NULL;
        while (curNode != p) 
            curNode = (curNode->val > p->val) ? (candidate = curNode)->left : curNode->right;
            
        return candidate;
    }
};

/* Analysis:
The if case is actually not needed. We can combine the two cases by realizing that the key logic is to find the smallest node in the tree that is larger than the value of p. Why not just do a root-to-leaf search passing through p, and return the last such node?

Time: O(h), where h is the height of the tree.
Space: O(1).
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (!root || !p) return NULL;
        TreeNode *curNode = root;
        TreeNode *candidate = NULL;
        
        while (curNode)
            curNode = (curNode->val > p->val) ? (candidate = curNode)->left : curNode->right;
            
        return candidate;
    }
};
