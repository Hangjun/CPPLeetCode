/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.
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
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        if (root->left == NULL && root->right == NULL) return true;
        TreeNode *curNode = root, *preNode = NULL;
        stack<TreeNode *> s;
        while (curNode != NULL || !s.empty()) {
            if (curNode != NULL) {
                s.push(curNode);
                curNode = curNode->left;
            } else {
                TreeNode *readyNode = s.top();
                s.pop();
                if (preNode != NULL && preNode->val >= readyNode->val)
                    return false;
                preNode = readyNode;
                curNode = readyNode->right;
            }
        }
        return true;
    }
};
