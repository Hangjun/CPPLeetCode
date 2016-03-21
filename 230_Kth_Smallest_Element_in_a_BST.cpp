/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

    Try to utilize the property of a BST.
    What if you could modify the BST node's structure?
    The optimal runtime complexity is O(height of BST).

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
    int kthSmallest(TreeNode* root, int k) {
        TreeNode *curNode = root;
        stack<TreeNode *> s;
        int counter = 0;
        while (curNode || !s.empty()) {
            if (curNode != NULL) {
                s.push(curNode);
                curNode = curNode->left;
            } else {
                TreeNode *tmpNode = s.top();
                s.pop();
                if (++counter == k) return tmpNode->val;
                curNode = tmpNode->right;
            }
        }
    }
};
