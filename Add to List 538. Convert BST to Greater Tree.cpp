/*
Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
*/

/*
Solution: We can use a modified inorder travel: right-mid-left. At every stage of the iteration, the rightmost node does not need to be modified anymore as it already has the largest value for that moment. Therefore we can keep a global curSum variable that records the total sum so far.
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
    TreeNode* convertBST(TreeNode* root) {
        int curSum = 0;
        travel(root, curSum);
        return root;
    }
    
    void travel(TreeNode *curNode, int &curSum) {
        if (!curNode) return;
        if (curNode->right) travel(curNode->right, curSum);
        
        // now curNode is the right most node
        curNode->val = (curSum += curNode->val);
        
        travel(curNode->left, curSum);
    }
};
