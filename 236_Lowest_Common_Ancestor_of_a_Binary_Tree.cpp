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

// A staightfoward algorithm is to compare the paths from root to p and root to q. The first node that's different is the LCA:

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
        
        // find the first differnt node in the two paths
        int n = min(pathToP.size(), pathToQ.size());
        int i = 0;
        while (i < n && pathToP[i] == pathToQ[i]) i++;
        if (i < n) return pathToP[i-1];
        return i == pathToP.size() ? p : q;
    }
    
    vector<TreeNode *> findPath(TreeNode *start, TreeNode *end) {
        vector<TreeNode *> path;
        vector<TreeNode *> tmpPath;
        findPathDFS(start, end, tmpPath, path);
        return path;
    }
    
    void findPathDFS(TreeNode *curNode, const TreeNode *target, vector<TreeNode *> &tmpPath, vector<TreeNode *> &path) {
        if (!path.empty()) return;
        tmpPath.push_back(curNode);
        if (curNode == target) {
            path = tmpPath;
            return;
        }
            
        if (curNode->left) findPathDFS(curNode->left, target, tmpPath, path);
        if (curNode->right) findPathDFS(curNode->right, target, tmpPath, path);
        
        tmpPath.pop_back();
    }
};

/* Remark:
The above solution traverses the paths twice, and has to store the path. Instead of going from top-dowm, we traverse from the 
bottom, and once we reach a node which matches one of the two nodes, we pass it up to its parent. The parent would then test 
its left and right subtree if each contain one of the two nodes. If yes, then the parent must be the LCA and we pass its parent 
up to the root. If not, we pass the lower node which contains either one of the two nodes (if the left or right subtree 
contains either p or q), or NULL (if both the left and right subtree does not contain either p or q) up.
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
        if (!root || !p || !q) return NULL;
        if (root == p || root == q) return root;
        TreeNode *leftLCA = lowestCommonAncestor(root->left, p, q);
        TreeNode *rightLCA = lowestCommonAncestor(root->right, p, q);
        
        if (leftLCA && rightLCA) return root;
        return leftLCA ? leftLCA : rightLCA;
    }
};

