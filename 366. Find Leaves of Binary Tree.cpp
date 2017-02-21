/*
Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.

Example:
Given binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Returns [4, 5, 3], [2], [1].

Explanation:
1. Removing the leaves [4, 5, 3] would result in this tree:

          1
         / 
        2          
2. Now removing the leaf [2] would result in this tree:

          1          
3. Now removing the leaf [1] would result in the empty tree:

          []         
Returns [4, 5, 3], [2], [1].
*/

/*
Grouping together all the nodes at the same level does not work, but computing the height (distance from the node to the deepest leaf) works.
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
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        computeHeightDFS(root, res);
        return res;
    }
    
    int computeHeightDFS(TreeNode *curNode, vector<vector<int>> &res) {
        if (!curNode) return -1; // height of leaf node is 0
        int height = 1 + max(computeHeightDFS(curNode->left, res), computeHeightDFS(curNode->right, res));
        if (height == res.size()) res.push_back(vector<int>()); // new height discovered
        res[height].push_back(curNode->val);
        return height;
    }
};
