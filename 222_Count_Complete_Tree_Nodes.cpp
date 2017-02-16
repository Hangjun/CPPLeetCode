/*
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as 
possible. It can have between 1 and 2h nodes inclusive at the last level h.
*/


// Time O((logn)^2).
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
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        int leftHeight = 0;
        int rightHeight = 0;
        TreeNode *l = root, *r = root;
        while (l != NULL) {
            ++leftHeight;
            l = l->left;
        }
        while (r != NULL) {
            ++rightHeight;
            r = r->right;
        }
        if (leftHeight == rightHeight) return pow(2, leftHeight) - 1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
