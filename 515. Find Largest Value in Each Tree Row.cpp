/*
You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        queue<TreeNode *> curLevel;
        queue<TreeNode *> nextLevel;
        curLevel.push(root);
        
        while (!curLevel.empty()) {
            int curMax = INT_MIN;
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevel.pop();
                curMax = max(curMax, curNode->val);
                if (curNode->left) nextLevel.push(curNode->left);
                if (curNode->right) nextLevel.push(curNode->right);
            }
            res.push_back(curMax);
            swap(curLevel, nextLevel);
        }
        
        return res;
    }
};
