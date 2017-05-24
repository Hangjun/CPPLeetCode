/*
Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:

The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
*/

/*
Analysis: This is a tree traversal problem. The key is which traversal order should we use. Well, the question is: at every node what information do we need to perform the current comptuation, and what information should we pass onward?

At every node, we need to know the total sum from the left subtree and the total sum from the right subtree. That's all we need to compute the current tilt and add to the final result. We also need to pass onward the sum of the left subtre + the sum of the right subtree + the value of the current node. This is suggests that postorder traversal is the way to go.
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
    int findTilt(TreeNode* root) {
        int res = 0;
        findTiltRecur(root, res);
        return res;
    }
    
    int findTiltRecur(TreeNode *curNode, int &res) {
        if (!curNode) return 0;
        
        int leftSum = findTiltRecur(curNode->left, res);
        int rightSum = findTiltRecur(curNode->right, res);
        res += abs(rightSum - leftSum);
        
        return leftSum + curNode->val + rightSum;
    }
};
