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

/* 
Of course we can first produce the preorder traversal list, and then walk the list to modify the left/right pointers. However, this is very inefficient both time-wise and space-wise. Intuitively, the solution needs to:
1. traverse the tree only once
2. takes O(1) space.

One key observation needed in order to come up with such a solution is that, at every node, we can connect its left subtree's rightmost leaf node with its right child. This is because the rightmost leaf nod of the left subtree is exactly the preorder predecessor of the right child. We can interative perform this update, and sequence out the tree.
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
        TreeNode *curNode = root;
        while (curNode) {
            if (curNode->left) {
                TreeNode *prevNode = curNode->left;
                while (prevNode->right) prevNode = prevNode->right;
                prevNode->right = curNode->right;
                curNode->right = curNode->left;
                curNode->left = NULL;
            }
            
            curNode = curNode->right;
        }
    }
};

/* 
To do this recursively, notice that we have modify the post order traversal to construct the flattening links. The preorder traverses as mid-left-right, we can simply recurse on right-left-mid.
*
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
        flatten(root->right);
        flatten(root->left);
        root->right = prevNode;
        root->left = NULL;
        prevNode = root;
    }

private:
    TreeNode *prevNode = NULL;
};

// Bruteforce solution.
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
