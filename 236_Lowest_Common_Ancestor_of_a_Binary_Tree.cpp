/*
 Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return NULL;
        vector<TreeNode *> pathToP = findPath(root, p);
        vector<TreeNode *> pathToQ = findPath(root, q);
        int n = min(pathToP.size(), pathToQ.size());
        int i = 0;
        while (i < n && pathToP[i] == pathToQ[i]) i++;
        if (i < n) return pathToP[i-1]; // i is at least 1 (root lies on both paths)
        // now i == n
        return i == pathToP.size() ? p : q;
    }
    
    vector<TreeNode *> findPath(TreeNode *root, TreeNode *target) {
        vector<TreeNode *> path;
        findPathDFS(root, target, path);
        return path;
    }
    
    bool findPathDFS(TreeNode *curNode, const TreeNode *target, vector<TreeNode *> &path) {
        path.push_back(curNode);
        // check for terminating condition
        if (curNode == target) return true; 
        
        if (curNode->left && findPathDFS(curNode->left, target, path)) return true;
        if (curNode->right && findPathDFS(curNode->right, target, path)) return true;
        
        // backtrack
        path.pop_back();
        return false;
    }
};
