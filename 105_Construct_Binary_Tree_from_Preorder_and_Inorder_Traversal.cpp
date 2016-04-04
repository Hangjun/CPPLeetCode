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
        if (preorder.size() != inorder.size())
            return NULL;
        int n = preorder.size();
        return buildTreeRecur(preorder, inorder, 0, n-1, 0, n-1);
    }
    
    TreeNode *buildTreeRecur(vector<int> &preorder, vector<int> &inorder, int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd)
            return NULL;
        TreeNode *root = new TreeNode(preorder[preStart]);
        int rootIndex = -1;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == root->val) {
                rootIndex = i;
                break;
            }
        }
        if (rootIndex == -1) return NULL;
        //left subtree size = rootIndex - inStart
        //right subtree size = inEnd - rootIndex
        int leftTreeSize = rootIndex - inStart;
        int rightTreeSize = inEnd - rootIndex;
        root->left = buildTreeRecur(preorder, inorder, preStart+1, preStart+leftTreeSize, inStart, rootIndex-1);
        root->right = buildTreeRecur(preorder, inorder, preEnd-rightTreeSize+1, preEnd, rootIndex+1, inEnd);
        return root;
    }
};
