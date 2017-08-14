/*
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
*/

/*
Solution: a lazy man's solution would be to first compute the inorder traversal of the BST and then the problem becomes the original two sum. One can use Morris traversal to reduce the space complexity to O(1), but let's be lazy here and use O(n) space:

Time: O(n), Space: O(n).
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
    bool findTarget(TreeNode* root, int k) {
        vector<int> list;
        inorderTraverse(root, list);
        int left = 0, right = list.size()-1;
        
        while (left < right) {
            int curSum  = list[left] + list[right];
            if (curSum == k) return true;
            else if (curSum < k) left++;
            else right--;
        }
        
        return false;
    }
    
    void inorderTraverse(TreeNode *curNode, vector<int> &list) {
        if (!curNode) return;
        if (curNode->left) inorderTraverse(curNode->left, list);
        list.push_back(curNode->val);
        if (curNode->right) inorderTraverse(curNode->right, list);
    }
};
