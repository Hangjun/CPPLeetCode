/*
Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,
              5
             / \
            1   5
           / \   \
          5   5   5
return 4.
*/

/*
This problem is very similary to Problem 333 (https://leetcode.com/problems/largest-bst-subtree/?tab=Description). They both share the property that, there is this certain structure that the left subtree, the right substree as well as the whole subtree rooted at the current node need to all satisfy in order to pass some information upstream bottom-to-top.

In this case, we are only interested the number of univalue substrees already computed, and also whether the left/right subtrees are univalued.
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
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        isUnivalDFS(root, count);
        return count;
    }
    
    bool isUnivalDFS(TreeNode *curNode, int &count) {
        if (!curNode) return true;
        bool leftU = isUnivalDFS(curNode->left, count);
        bool rightU = isUnivalDFS(curNode->right, count);
        
        if (leftU && rightU) {
            if ((!curNode->left || curNode->val == curNode->left->val) && (!curNode->right || curNode->val == curNode->right->val)) {
                ++count;
                return true;
            }
        }
        
        return false;
    }  
};

/* Remark: with the same technique, we can also compute the largest univalued subtree. More generally, define a specific tree structure S, this same technique can be used to compute:
1. number of substrees satisfying this property;
2. largest subtree satisfying this property.

This is an important algorithmic paradigm for this particular tree problems.
*/
