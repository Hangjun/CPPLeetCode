/*
Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        if (!root) return res;
        queue<TreeNode *> curLevel;
        queue<TreeNode *> nextLevel;
        curLevel.push(root);
        
        // loop invariant: at the beginning of each loop, the average of curLevel has not been computed
        while (!curLevel.empty()) {
            double curSum = 0;
            int curLevelSize = curLevel.size();
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevel.pop();
                curSum += (double) curNode->val;
                if (curNode->left) nextLevel.push(curNode->left);
                if (curNode->right) nextLevel.push(curNode->right);
            }
            // compute curLevel's average
            res.push_back(curSum / curLevelSize);
            swap(curLevel, nextLevel);
        }
        
        return res;
    }
};
