/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---

You should return [1, 3, 4]. 
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
    vector<int> rightSideView(TreeNode* root) {
        // first do a level order reverseal, then scan each leve, return the right most node
        vector<int> rightSideNode;
        vector<vector<int>> levels = levelOrder(root);
        for (int i = 0; i < levels.size(); i++) {
            rightSideNode.push_back(levels[i].back());
        }
        return rightSideNode;
    }
    
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode *> curLevel;
        queue<TreeNode *> nextLevel;
        curLevel.push(root);
        while (!curLevel.empty()) {
            vector<int> curLevelVal;
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevelVal.push_back(curNode->val);
                if (curNode->left)
                    nextLevel.push(curNode->left);
                if (curNode->right)
                    nextLevel.push(curNode->right);
                curLevel.pop();
            }
            result.push_back(curLevelVal);
            swap(curLevel, nextLevel);
        }
        return result;
    }
};
