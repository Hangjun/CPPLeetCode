/*
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7
*/

/*
The trick here is, when we find the node to be deleted, we replace it's value with its successor's value, and recursively delete its successor. This way the BST structure is preserved. We can do this recursively or iteratively.
*/

// Recursive solution.
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else if (root->val < key) {
            root->right= deleteNode(root->right, key);
        } else {
            // find the successor of root and recursively delete the successor
            if (root->left && root->right) {
                TreeNode *succ = findMin(root->right);
                root->val = succ->val;
                root->right = deleteNode(root->right, succ->val);
            } else if (root->left) {
                return root->left;
            } else {
                return root->right;
            }
        }
        return root;
    }
    
private:
    TreeNode *findMin(TreeNode *root) {
        while (root->left) root = root->left;
        return root;
    }
};

// Iterative solution.
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode *curNode = root;
        TreeNode *prevNode = NULL;
        while (curNode && curNode->val != key) {
            prevNode = curNode;
            if (curNode->val < key) curNode = curNode->right;
            else curNode = curNode->left;
        }
        
        if (!prevNode) return deleteNodeHelper(curNode);
        
        if (prevNode->left == curNode) {
            prevNode->left = deleteNodeHelper(curNode);
        } else {
            prevNode->right = deleteNodeHelper(curNode);
        }
        
        return root;
    }
    
    TreeNode *deleteNodeHelper(TreeNode *root) {
        if (!root) return NULL;
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode *next = root->right;
        TreeNode *prevNode = NULL;
        while (next->left) {
            prevNode = next;
            next = next->left;
        }
        next->left = root->left;
        if (root->right != next) {
            prevNode->left = next->right;
            next->right = root->right;
        }
        
        return next;
    }
};
