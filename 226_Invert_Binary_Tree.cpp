/*
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9

to

     4
   /   \
  7     2
 / \   / \
9   6 3   1
*/

// Recursive Solution
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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        TreeNode *tmpNode = root->left;
        root->left = root->right;
        root->right = tmpNode;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

// Iterative Solution
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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        queue<TreeNode *> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode *curNode = q.front();
            q.pop();
            TreeNode *tmp = curNode->left;
            curNode->left = curNode->right;
            curNode->right = tmp;
            if (curNode->left) q.push(curNode->left);
            if (curNode->right) q.push(curNode->right);
        }
        
        return root;
    }
};
