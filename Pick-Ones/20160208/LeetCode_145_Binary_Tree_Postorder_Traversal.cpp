/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?
*/

// Submission #1: Accepted.
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        stack<TreeNode *> preStack;
        preStack.push(root);
        stack<TreeNode *> readyStack;
        while (!preStack.empty()) {
            TreeNode *curNode = preStack.top();
            preStack.pop();
            readyStack.push(curNode);
            if (curNode->left) {preStack.push(curNode->left);}
            if (curNode->right) {preStack.push(curNode->right);}
        }
        while (!readyStack.empty()) {
            res.push_back(readyStack.top()->val);
            readyStack.pop();
        }
        return res;
    }
};
