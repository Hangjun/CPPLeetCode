/*
Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

Note:
A subtree must include all of its descendants.
Here's an example:
    10
    / \
   5  15
  / \   \ 
 1   8   7
The Largest BST Subtree in this case is the highlighted one. 
The return value is the subtree's size, which is 3.
Hint:

You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will result in O(nlogn) time complexity.
Follow up:
Can you figure out ways to solve it with O(n) time complexity?
*/

/* 
The top-down approach is O(nlogn). To achieve O(n) time, we use the bottom-up approach. Notice the similarity of this problem with the ski program. 

At every node, there are three tasks:
1. Check BST-ness of its left subtree and right subtree.
2. Compute the max size BST in left and right subtrees.
3. According to the result of 1, update the max size BST at the subtree rooted at the current node.
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
    int largestBSTSubtree(TreeNode* root) {
        if (!root) return 0;
        int res = 1;
        int minVal = INT_MIN, maxVal = 0;
        isBST(root, minVal, maxVal, res);
        return res;
    }
    
    bool isBST(TreeNode *curNode, int &minVal, int &maxVal, int &res) {
        if (!curNode) return true;
        int leftSize = 0, rightSize = 0;
        int leftMin, leftMax, rightMin, rightMax;
        leftMin = rightMin = INT_MIN;
        leftMax = rightMax = 0;
        bool leftB = isBST(curNode->left, leftMin, leftMax, leftSize);
        bool rightB = isBST(curNode->right, rightMin, rightMax, rightSize);
        
        if (leftB && rightB) {
            if ((!curNode->left || curNode->val > leftMax) && (!curNode->right || curNode->val < rightMin)) {
                res = 1 + leftSize + rightSize;
                minVal = curNode->left ? leftMin : curNode->val;
                maxVal = curNode->right ? rightMax : curNode->val;
                return true;
            }
        }
        
        res = max(leftSize, rightSize);
        return false;
    }
};
