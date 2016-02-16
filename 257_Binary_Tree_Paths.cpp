/*
 Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5

All root-to-leaf paths are:

["1->2->5", "1->3"]
*/


/* Depth First Search:
Several key points:
1. The return format for a path is a string connecting nodes by "->". 
2. DFS until we reach a leaf node. 
3. When we return from a leaf node, we need delete the leaf node from our local path and back track to its parent.
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (!root) return res;
        vector<TreeNode *> path;
        path.push_back(root);
        binaryTreePathsDFS(root, path, res);
        return res;
    }
    
    void binaryTreePathsDFS(TreeNode *curNode, vector<TreeNode *> &path, vector<string> &res) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            // convert path into string
            string s = "";
            int i;
            for (i = 0; i < path.size()-1; i++) {
                s += to_string(path[i]->val) + "->";
            }
            s += to_string(path[i]->val);
            res.push_back(s);
            return;
        }
        
        // DFS step
        if (curNode->left) {
            path.push_back(curNode->left);
            binaryTreePathsDFS(curNode->left, path, res);
            path.pop_back();
        }
        
        if (curNode->right) {
            path.push_back(curNode->right);
            binaryTreePathsDFS(curNode->right, path, res);
            path.pop_back();
        }
    }
};


