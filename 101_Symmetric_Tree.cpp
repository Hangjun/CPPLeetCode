/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3

Note:
Bonus points if you could solve it both recursively and iteratively.

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymHelper(root->left, root->right);
    }
    
    bool isSymHelper(TreeNode *l, TreeNode *r) {
        if (l == NULL) return r == NULL;
        if (r == NULL) return l == NULL;
        if (l->val != r->val) return false;
        if (!isSymHelper(l->right, r->left)) return false;
        if (!isSymHelper(l->left, r->right)) return false;
        return true;
    }
};

/* 
Remark: The key of the recursive solution is to realize that the recursive step is to compare two subtrees, not necessarily belonging to the same parent node.
/*

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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        vector<TreeNode *> level;
        level.push_back(root);
        int levelSize = 1;
        
        while (levelSize > 0) {
            // populate the next level nodes, including NULL children
            int i = 0; 
            while (i < levelSize) {
                TreeNode *curNode = level[i];
                if (curNode != NULL) {
                    level.push_back(curNode->left);
                    level.push_back(curNode->right);
                }
                i++;
            }
            int start = 0, end = levelSize-1;
            while (start < end) {
                int left = level[start] == NULL ? -1 : level[start]->val;
                int right = level[end] == NULL ? -1 : level[end]->val;
                if (left != right) return false;
                start++;
                end--;
            }
            // remove the previous level from the vector
            level.erase(level.begin(), level.begin() + levelSize);
            // recompute size of the next level
            levelSize = level.size();
        }
        
        return true;
    }
};
