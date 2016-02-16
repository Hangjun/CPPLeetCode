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


/* Key points:
1. We need to return all the legal paths. Thus the DFS cannot simply return a bool indicating whether A path exists. 
2. There are again several styles of DFS: (1) push before recurse, clean up after returning; (2) push after recurse, clean up before returning; 
(3) push after recurse, clean up before returning.
*/

// DFS version #1:
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
        pathSumDFS(root, sum, path, res);
        return res;
    }
    
    void pathSumDFS(TreeNode *curNode, int target, vector<int> &path, vector<vector<int>> &res) {
        // terminating condition: root-to-leaf path
        if (curNode->left == NULL && curNode->right == NULL) {
            if (target == curNode->val) {
                res.push_back(path);
            }
            return;
        }
        
        // continue recursing on the child nodes
        if (curNode->left) {
            path.push_back(curNode->left->val);
            pathSumDFS(curNode->left, target-curNode->val, path, res);
            path.pop_back();
        }
        
        if (curNode->right) {
            path.push_back(curNode->right->val);
            pathSumDFS(curNode->right, target-curNode->val, path, res);
            path.pop_back();
        }
    }
};


// DFS version #2: works but looks awkward (lines 96 - 100).
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
        pathSumDFS(root, sum, path, res);
        return res;
    }
    
    void pathSumDFS(TreeNode *curNode, int target, vector<int> &path, vector<vector<int>> &res) {
        // recursion invariant: try curNode for this recursion
        path.push_back(curNode->val);
        // terminating condition: root-to-leaf path
        if (curNode->left == NULL && curNode->right == NULL) {
            if (target == curNode->val) {
                res.push_back(path);
            }
        }
        
        // continue recursing on the child nodes
        if (curNode->left) pathSumDFS(curNode->left, target-curNode->val, path, res);
        if (curNode->right) pathSumDFS(curNode->right, target-curNode->val, path, res);
        
        // no path that sum up to target can be found eminating from curNode: backtrack
        path.pop_back();
    }
};


// DFS version 2': Local solution passed in by copy instead of by reference, so that no manual backtracking needed upon returning.
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
        pathSumDFS(root, sum, path, res);
        return res;
    }
    
    void pathSumDFS(TreeNode *curNode, int target, vector<int> path, vector<vector<int>> &res) {
        path.push_back(curNode->val);
        if (curNode->left == NULL && curNode->right == NULL) {
            if (target == curNode->val) {
                res.push_back(path);
            }
            return; // no explicit clean up needed
        }
        
        if (curNode->left) pathSumDFS(curNode->left, target - curNode->val, path, res);
        if (curNode->right) pathSumDFS(curNode->right, target - curNode->val, path, res);
    }
};


// DFS version #3: Null node checking logic slightly modified.
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
        vector<int> path;
        pathSumDFS(root, sum, path, res);
        return res;
    }
    
    void pathSumDFS(TreeNode *curNode, int target, vector<int> &path, vector<vector<int>> &res) {
        if (curNode == NULL) return;
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            if (target == curNode->val) {
                path.push_back(curNode->val);
                res.push_back(path);
                path.pop_back();
            }
            return;
        }
        // curNode is not leaf node, continue recursing
        path.push_back(curNode->val);
        pathSumDFS(curNode->left, target-curNode->val, path, res);
        pathSumDFS(curNode->right, target-curNode->val, path, res);
        
        // backtrack before returning
        path.pop_back();
    }
};


// DFS version #3': Passing by copy trick used.
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
        vector<int> path;
        pathSumDFS(root, sum, path, res);
        return res;
    }
    
    void pathSumDFS(TreeNode *curNode, int target, vector<int> path, vector<vector<int>> &res) {
        if (curNode == NULL) return;
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            if (target == curNode->val) {
                path.push_back(curNode->val);
                res.push_back(path);
            }
            return;
        }
        // curNode is not leaf node, continue recursing
        path.push_back(curNode->val);
        pathSumDFS(curNode->left, target-curNode->val, path, res);
        pathSumDFS(curNode->right, target-curNode->val, path, res);
    }
};

