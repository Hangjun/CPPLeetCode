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
        int n = nums.size();
        int left = 0, right = n-1;
        return sortedArrayToBSTRecur(nums, left, right);
    }
    TreeNode* sortedArrayToBSTRecur(vector<int> &nums, int start, int end) {
        if (start > end) return NULL;
        int mid = start + (end - start)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBSTRecur(nums, start, mid-1);
        root->right = sortedArrayToBSTRecur(nums, mid+1, end);
        return root;
    }
};
