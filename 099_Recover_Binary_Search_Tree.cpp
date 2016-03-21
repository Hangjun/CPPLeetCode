/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? 
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
    void recoverTree(TreeNode* root) {
        if (root == NULL) return;
        bool found = false;
        TreeNode *n1 = NULL, *n2 = NULL;
        TreeNode *curNode = root, *preNode, *parentNode = NULL;
        while (curNode != NULL) {
            if (curNode->left == NULL) {
                if (parentNode && parentNode->val > curNode->val) {
                    if (found == false) {
                        n1 = parentNode;
                        found = true;
                    }
                    //it is important to set n2 at this point
                    n2 = curNode;
                }
                
                parentNode = curNode;
                curNode = curNode->right;
            } else {
                preNode = curNode->left;
                while (preNode->right != NULL && preNode->right != curNode)
                    preNode = preNode->right;
                if (preNode->right == NULL) {
                    preNode->right = curNode;
                    curNode = curNode->left;
                } else {
                    preNode->right = NULL;
                    if (parentNode->val > curNode->val) {
                        if (found == false) {
                            n1 = parentNode;
                            found = true;
                        }
                        //it is important to set n2 at this point
                        n2 = curNode;
                    }
                    
                    parentNode = curNode;
                    curNode = curNode->right;
                }
            }
        }
        //swap n1 and n2
        if(n1 != NULL && n2 != NULL) {
            int tmp = n1->val;
            n1->val = n2->val;
            n2->val = tmp;
        }
    }
};
