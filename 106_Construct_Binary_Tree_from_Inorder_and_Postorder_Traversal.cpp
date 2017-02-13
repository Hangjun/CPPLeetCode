/*
Given inorder and postorder traversal of a tree, construct the binary tree.

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() != postorder.size()) return NULL;
        int n = inorder.size();
        return buildTreeRecur(inorder, postorder, 0, n-1, 0, n-1);
    }
    
    TreeNode *buildTreeRecur(vector<int> &inorder, vector<int> &postorder, int inStart, int inEnd, int postStart, int postEnd) {
        if (inStart > inEnd || postStart > postEnd) return NULL;
        TreeNode *root = new TreeNode(postorder[postEnd]);
        
        int rootIndex = 0;
        while (inorder[rootIndex] != root->val && rootIndex <= inEnd) rootIndex++;
        
        int leftTreeSize = rootIndex-inStart;
        int rightTreeSize = inEnd-rootIndex;
        
        root->left = buildTreeRecur(inorder, postorder, inStart, rootIndex-1, postStart, postStart+leftTreeSize-1);
        root->right = buildTreeRecur(inorder, postorder, rootIndex+1, inEnd, postEnd-rightTreeSize, postEnd-1);
        
        return root;
    }
};
