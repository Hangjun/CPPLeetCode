/*
Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
    1
   / \
  2   3
 / \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
   4
  / \
 5   2
    / \
   3   1  
*/

// Recursive solution. Time O(n), Space O(nlogn).
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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left)  return root;
        TreeNode *newRoot = upsideDownBinaryTree(root->left);
        root->left->left = root->right;
        root->left->right = root;
        root->left = NULL;
        root->right = NULL;
        
        return newRoot;
    }
};

// Iterative solution. Time O(n), Space O(1).
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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left)  return root;
        TreeNode *prevNode, *curNode, *nextNode, *tmpNode;
        
        prevNode = nextNode = tmpNode = NULL;
        curNode = root;
        
        while (curNode) {
            nextNode = curNode->left;
            
            curNode->left = tmpNode;
            tmpNode = curNode->right;
            curNode->right = prevNode;
            
            prevNode = curNode;
            curNode = nextNode;
        }
        
        return prevNode;
    }
};
