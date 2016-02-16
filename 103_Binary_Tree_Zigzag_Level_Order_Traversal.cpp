/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:

[
  [3],
  [20,9],
  [15,7]
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        queue<TreeNode *> curLevel;
        curLevel.push(root);
        queue<TreeNode *> nextLevel;
        bool flag = false;
        
        while (!curLevel.empty()) {
            vector<int> curLevelVals;
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevel.pop();
                curLevelVals.push_back(curNode->val);
                if (curNode->left) {nextLevel.push(curNode->left);}
                if (curNode->right) {nextLevel.push(curNode->right);}
            }
            
            if (flag) {
                reverse(curLevelVals.begin(), curLevelVals.end());
                flag = false;
            } else {flag = true;}
            
            res.push_back(curLevelVals);
            swap(curLevel, nextLevel);
        }
        
        return res;
    }
};
