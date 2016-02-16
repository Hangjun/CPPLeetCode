/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/* Submission #1: Failed:
Submission Result: Wrong Answer
Input: [1]
Output: []
Expected: [1] 
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
    vector<int> inorderTraversal(TreeNode* root) {
        // left-mid-right
        vector<int> res;
        if (!root) return res;
        stack<TreeNode *> st;
        TreeNode *curNode = root;
        while (!curNode || !st.empty()) {
            if (!curNode) {
                st.push(curNode);
                curNode = curNode->left;
            } else { // curNode == NULL, backtrack
                TreeNode *tmpNode = st.top();
                st.pop();
                res.push_back(tmpNode->val);
                curNode = tmpNode->right;
            }
        }
        
        return res;
    }
};

/* Analysis:
Typo on lines 41 and 42. In the future write out if (curNode != NULL) instead of if (curNode) if not absolutely certain.
*/

// Submission #2: Accepted.
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
    vector<int> inorderTraversal(TreeNode* root) {
        // left-mid-right
        vector<int> res;
        if (!root) return res;
        stack<TreeNode *> st;
        TreeNode *curNode = root;
        while (curNode || !st.empty()) {
            if (curNode) {
                st.push(curNode);
                curNode = curNode->left;
            } else { // curNode == NULL, backtrack
                TreeNode *tmpNode = st.top();
                st.pop();
                res.push_back(tmpNode->val);
                curNode = tmpNode->right;
            }
        }
        
        return res;
    }
};
