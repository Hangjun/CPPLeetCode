/* Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> levels;
        if (root == NULL) return levels;
        queue<TreeNode *> curLevel;
        queue<TreeNode *> nextLevel;
        curLevel.push(root);
        
        while (!curLevel.empty()) {
            vector<int> level;
            level.clear();
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                level.push_back(curNode->val);
                curLevel.pop();
                if (curNode->left) {
                    nextLevel.push(curNode->left);
                }
                if (curNode->right) {
                    nextLevel.push(curNode->right);
                }
            }
            levels.push_back(level);
            swap(curLevel, nextLevel);
        }
        return levels;
    }
};
