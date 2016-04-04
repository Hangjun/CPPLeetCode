/*
 Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:

   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

click to show hints.
Hints:

If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.
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
    void flatten(TreeNode* root) {
         root = flattenDFS(root);
    }
    
    TreeNode *flattenDFS(TreeNode *root) {
        if (!root) return NULL;
        TreeNode *leftTail = flattenDFS(root->left);
        TreeNode *rightTail = flattenDFS(root->right);
        if (leftTail) {
            TreeNode *tmp = root->right;
            root->right = root->left;
            root->left = NULL;
            leftTail->right = tmp;
        }
        //if rightTail exists, return it first. This order if critial.
        if (rightTail) return rightTail;
        if (leftTail) return leftTail;
        //if none of leftTail or rightTail exist, return root
        return root;
    }
};

// Another Solution:
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
    void flatten(TreeNode* root) {
        if (!root) return;
        vector<TreeNode *> preorderNodes = preorderTraversal(root);
        for (int i = 0; i < preorderNodes.size()-1; i++) {
            preorderNodes[i]->left = NULL;
            preorderNodes[i]->right = preorderNodes[i+1];
        }
    }
    
    vector<TreeNode *> preorderTraversal(TreeNode* root) {
        //mid->left->right
        vector<TreeNode *> preorderNodes;
        if (!root)  return preorderNodes;
        stack<TreeNode *> nodes;
        TreeNode *curNode = root;
        while (!nodes.empty() || curNode != NULL) {
            if (curNode != NULL) {
                preorderNodes.push_back(curNode);
                nodes.push(curNode);
                curNode = curNode->left;
            } else {
                TreeNode *tmpNode = nodes.top();
                nodes.pop();
                curNode = tmpNode->right;
            }
        }
        return preorderNodes;
    }
};
