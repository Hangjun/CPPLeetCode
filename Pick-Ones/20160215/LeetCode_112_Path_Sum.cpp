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

/* Submission #1: Failed:
Wrong Answer:

Input: [1]
1
Output: false
Expected: true

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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        vector<TreeNode *> path;
        path.push_back(root);
        return hasPathSumDFS(root, path, sum);
    }
    
    bool hasPathSumDFS(TreeNode *curNode, vector<TreeNode *> &path, int sum) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            return sum == 0;
        }
        
        // DFS step on curNode's children
        if (curNode->left) {
            path.push_back(curNode->left);
            if (hasPathSumDFS(curNode->left, path, sum - curNode->val)) return true;
            path.pop_back();
        }
        
        if (curNode->right) {
            path.push_back(curNode->right);
            if (hasPathSumDFS(curNode->right, path, sum - curNode->val)) return true;
            path.pop_back();
        }
        
        // the path starint from curNode does not sum up to the desired value
        return false;
    }
};

/* Submission #2: Failed:
Wrong Answer:

Input: [1,2]
2
Output: true
Expected: false
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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        vector<TreeNode *> path;
        path.push_back(root);
        return hasPathSumDFS(root, path, sum - root->val);
    }
    
    bool hasPathSumDFS(TreeNode *curNode, vector<TreeNode *> &path, int sum) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            return sum == 0;
        }
        
        // DFS step on curNode's children
        if (curNode->left) {
            path.push_back(curNode->left);
            if (hasPathSumDFS(curNode->left, path, sum - curNode->val)) return true;
            path.pop_back();
        }
        
        if (curNode->right) {
            path.push_back(curNode->right);
            if (hasPathSumDFS(curNode->right, path, sum - curNode->val)) return true;
            path.pop_back();
        }
        
        // the path starint from curNode does not sum up to the desired value
        return false;
    }
};

/* Analysis:
This simple DFS problem again shows that you are still weak in the fundamentals. The reason the above implementations failed is that the 
terminating conditions are wrong. The DFS search starts from the root. The search terminates when we reaches a leaf node. At that moment, 
we should ask ourselves whether the current target equals to the leaf node's value, NOT whether it is zero. This one mistake shows that 
I have completely missed this problem. 

Also, the use of path is not necessary here. We only need to backtrack on the target value.
*/

// Submission #3: Accepted.
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
        vector<TreeNode *> path;
        path.push_back(root);
        return hasPathSumDFS(root, path, sum);
    }
    
    bool hasPathSumDFS(TreeNode *curNode, vector<TreeNode *> &path, int target) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            return target == curNode->val;
        }
        
        // DFS step on curNode's children
        if (curNode->left) {
            path.push_back(curNode->left);
            if (hasPathSumDFS(curNode->left, path, target - curNode->val)) return true;
            path.pop_back();
        }
        
        if (curNode->right) {
            path.push_back(curNode->right);
            if (hasPathSumDFS(curNode->right, path, target - curNode->val)) return true;
            path.pop_back();
        }
        
        // the path starint from curNode does not sum up to the desired value
        return false;
    }
};

// Submission #4: Accpeted: Getting rid of path.
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
    
    bool hasPathSumDFS(TreeNode *curNode, int &target) {
        // terminating condition
        if (curNode->left == NULL && curNode->right == NULL) {
            return target == curNode->val;
        }
        
        // DFS step on curNode's children
        if (curNode->left) {
            target -= curNode->val;
            if (hasPathSumDFS(curNode->left, target)) return true;
            target += curNode->val;
        }
        
        if (curNode->right) {
            target -= curNode->val;
            if (hasPathSumDFS(curNode->right, target)) return true;
            target += curNode->val;
        }
        
        // the path starint from curNode does not sum up to the desired value
        return false;
    }
};


/* Analysis:
why do we need to backtrack on the target value? We don't need intermediate path sums to be passed upward or downward. target should just be 
an int, not int &.
*/
// Submission #5: DFS logic further simplified: Accepted.
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

// Submission #6: Further simplied:
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
