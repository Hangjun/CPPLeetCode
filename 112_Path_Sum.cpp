/*
 Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/

// A more DFS looking implementation:
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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        return hasPathSumDFS(root, sum);
    }
    
    bool hasPathSumDFS(TreeNode *curNode, int target) {
        if (curNode->left == NULL && curNode->right == NULL) {
            return target == curNode->val;
        }
        
        if (curNode->left) {
            if (hasPathSumDFS(curNode->left, target - curNode->val)) {
                return true;
            }
        }
        if (curNode->right) {
            if (hasPathSumDFS(curNode->right, target - curNode->val)) {
                return true;
            }
        }
        
        return false;
    }
};

// But really the above implementation is doing the following simple recursion:
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
    bool hasPathSum(TreeNode* root, int sum) {
       if (!root) return false;
       if (root->left == NULL && root->right == NULL) return sum == root->val;
       return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

