/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty()) return NULL;
        return sortedArrayToBSTRecur(nums, 0, num.size()-1);
    }
    TreeNode* sortedArrayToBSTRecur(vector<int> &nums, int start, int end) {
        if (start > end) return NULL;
        int rootIndex = start + (end - start)/2;
        TreeNode *root = new TreeNode(nums[rootIndex]);
        
        root->left = sortedArrayToBSTRecur(nums, start, rootIndex-1);
        root->right = sortedArrayToBSTRecur(nums, rootIndex+1, end);
        
        return root;
    }
};
