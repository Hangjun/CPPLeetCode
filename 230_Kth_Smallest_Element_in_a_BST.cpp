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

// A straightforward solution is to note that the inorder traversal of a BST is a strictly increasing sequence:
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

/* Analysis:
One drawback of the above solution is that it is very slow if we are going to perform many such lookups. An improvement is to record the number of nodes of the subtree rooted at every node, so then we can perform a binary search to find the desired node. This is in spirit very similar to the quick select algorithm. If we can modify the tree structure, we can simply preprocess the tree to have have the count value for each node. In that case, each such lookup takes O(height) time.
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
        if (!root) return INT_MIN;
        int count = countNodes(root->left);
        if (k <= count) { // search left
            return kthSmallest(root->left, k);
        } else if (k > count + 1) {
            return kthSmallest(root->right, k-count-1);
        }
        return root->val;
    }
    
    int countNodes(TreeNode *root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
