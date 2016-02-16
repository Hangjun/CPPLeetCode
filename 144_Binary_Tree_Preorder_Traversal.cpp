/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
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
    vector<int> preorderTraversal(TreeNode* root) {
        // mid-left-right
        vector<int> res;
        if (!root) return res;
        TreeNode *curNode = root;
        stack<TreeNode *> st;
        
        while (curNode != NULL || !st.empty()) {
            if (curNode != NULL) {
                res.push_back(curNode->val);
                st.push(curNode);
                curNode = curNode->left;
            } else {
                TreeNode *tmpNode = st.top();
                st.pop();
                curNode = tmpNode->right;
            }
        }
        
        return res;
    }
};
