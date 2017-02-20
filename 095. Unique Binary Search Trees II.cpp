/*
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

/* 
If i is the root, then the left subtree must have nodes from 1 to i-1, and the right subtree i+1 to n. The root can take on any value from 1 to n, however, the left and right subtrees are restricted due to the BST structure.
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
    vector<TreeNode*> generateTrees(int n) {
        if (n <= 0) return vector<TreeNode *>{};
        return generateBST(1, n);
    }
    
    vector<TreeNode *> generateBST(int min, int max) {
        vector<TreeNode *> res;
        if (min > max) {
            res.push_back(NULL);
            return res;
        }
        
        for (int i = min; i <= max; i++) {
            vector<TreeNode *> leftSubtrees = generateBST(min, i-1);
            vector<TreeNode *> rightSubtrees = generateBST(i+1, max);
            
            // construct the |leftSubtrees| * |rightSubtrees| many BSTs rooted at i
            for (TreeNode *l : leftSubtrees) {
                for (TreeNode *r : rightSubtrees) {
                    TreeNode *root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        
        return res;
    }
};
