/*
Implementation of basic operations supported by a BST. Subject to be expanded.
*/

#include <iostream>
using namespace std;

class TreeNode {
private:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    
    TreeNode *findMin(TreeNode *root);
    void replaceNodeInParent(TreeNode *curNode, TreeNode *newNode);
    
public:
    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
    void deleteNode(TreeNode *root, int key);
};

TreeNode *TreeNode::findMin(TreeNode *root) {
    if (!root) return root;
    TreeNode *curNode = root;
    while (curNode->left) {
        curNode = curNode->left;
    }
    return curNode;
}

void TreeNode::replaceNodeInParent(TreeNode *curNode, TreeNode *newNode) {
    TreeNode *parentNode = curNode->parent;
    if (parentNode) {
        if (parentNode->left == curNode) {
            parentNode->left = newNode;
        } else {
            parentNode->right = newNode;
        }
    }
    if (newNode) {
        newNode->parent = parentNode;
    }
}

void TreeNode::deleteNode(TreeNode *root, int key) {
    // find the node to be deleted
    if (!root) return;
    if (root->val < key) {
        deleteNode(root->right, key);
    } else if (root->val > key) {
        deleteNode(root->left, key);
    } else {
        if (root->left && root->right) { // both children exist
            TreeNode *successor = findMin(root->right);
            root->val = successor->val;
            deleteNode(root->right, successor->val);
        } else if (root->left) { // only left child exists
            replaceNodeInParent(root, root->left);
        } else if (root->right) { // only right child exists
            replaceNodeInParent(root, root->right);
        } else { // leaf node
            replaceNodeInParent(root, NULL);
        }
    }
}


