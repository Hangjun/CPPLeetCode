/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree. 
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() != inorder.size()) return NULL;
        int n = preorder.size();
        return buildTreeRecur(preorder, inorder, 0, n-1, 0, n-1);
    }
    
    TreeNode *buildTreeRecur(vector<int> &preorder, vector<int> &inorder, int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) return NULL;
        // root is the first element of preorder vector
        TreeNode *root = new TreeNode(preorder[preStart]);
        
        // find the index of root node in inorder to find the left subtree and right subtree split
        int rootIndex = 0;
        /* 
         * preordern and inorder are from the same tree, so rootIndex must be well-defined
         */
        while (inorder[rootIndex] != root->val && rootIndex <= inEnd) rootIndex++; 
        
        int leftTreeSize = rootIndex - inStart;
        int rightTreeSize = inEnd - rootIndex;
        
        // recursively build left and right subtree
        root->left = buildTreeRecur(preorder, inorder, preStart+1, preStart+leftTreeSize, inStart, rootIndex-1);
        root->right = buildTreeRecur(preorder, inorder, preEnd-rightTreeSize+1, preEnd, rootIndex+1, inEnd);
        
        return root;
    }
};
