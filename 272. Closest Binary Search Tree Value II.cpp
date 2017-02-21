/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
Try to assume that each node has a parent pointer, it makes the problem much easier.
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
You would need two stacks to track the path in finding predecessor and successor node separately.
*/

/*
The idea is to store the predecessors and successors of the node closest to the target, and then perform a "merge sort" to find, from the predecessors and successors, the remaining closest nodes. 

We can store the predecessors and successors of the closest node in two stacks.

Time: O(logn + k)
Space: O(n)
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
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> res;
        vector<int> pred; // in descending order
        vector<int> succ; // in ascending order 
        inorder(root, target, pred, succ, k);
        int i = 0, j = 0;
        // "merge sort"
        while (res.size() < k) {
            if (i == pred.size()) {
                res.push_back(succ[j++]);
            } else if (j == succ.size()) {
                res.push_back(pred[i++]);
            } else if (succ[j] - target < target - pred[i]) {
                res.push_back(succ[j++]);
            } else {
                res.push_back(pred[i++]);
            }
        }
        
        return res;
    }
    
    void inorder(TreeNode *curNode, double target, vector<int> &pred, vector<int> &succ, int k) {
        if (!curNode) return;
        if (target <= curNode->val) {
            inorder(curNode->left, target, pred, succ, k);
            if (succ.size() >= k) return;
            succ.push_back(curNode->val);
            inorder(curNode->right, target, pred, succ, k);
        } else {
            inorder(curNode->right, target, pred, succ, k);
            if (pred.size() >= k) return;
            pred.push_back(curNode->val);
            inorder(curNode->left, target, pred, succ, k);
        }
    }
};
