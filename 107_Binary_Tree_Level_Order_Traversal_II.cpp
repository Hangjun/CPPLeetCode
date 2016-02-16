/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        stack<vector<int>> st;
        queue<TreeNode *> curLevel;
        curLevel.push(root);
        queue<TreeNode *> nextLevel;
        
        while (!curLevel.empty()) {
            vector<int> curLevelVals;
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevel.pop();
                curLevelVals.push_back(curNode->val);
                if (curNode->left) {nextLevel.push(curNode->left);}
                if (curNode->right) {nextLevel.push(curNode->right);}
            }
            st.push(curLevelVals);
            swap(curLevel, nextLevel);
        }
        
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        
        return res;
    }
};
