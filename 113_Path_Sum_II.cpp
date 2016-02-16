/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if (!root) return res;
        vector<int> path;
        path.push_back(root->val);
        pathSumDFS(root, path, sum, res);
        return res;
    }
    
    void pathSumDFS(TreeNode *curNode, vector<int> &path, int target, vector<vector<int>> &res) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            if (target == curNode->val) {res.push_back(path);}
            return;
        }
        
        // DFS step
        if (curNode->left) {
            path.push_back(curNode->left->val);
            pathSumDFS(curNode->left, path, target - curNode->val, res);
            path.pop_back();
        }
        
        if (curNode->right) {
            path.push_back(curNode->right->val);
            pathSumDFS(curNode->right, path, target - curNode->val, res);
            path.pop_back();
        }
    }
};
