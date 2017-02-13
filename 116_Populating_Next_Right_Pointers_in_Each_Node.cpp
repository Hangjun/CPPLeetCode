/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/


// Recursive Solution:
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        connectRecur(root->left, root->right);
    }
    
    void connectRecur(TreeLinkNode *l, TreeLinkNode *r) {
        if (!l) return;
        l->next = r;
        if (l->right) connectRecur(l->right, r->left);
        connectRecur(l->left, l->right);
        connectRecur(r->left, r->right);
    }
};



// Iterative Solution:
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) return;
        TreeLinkNode *lastHead = root;
        TreeLinkNode *curHead = NULL;
        TreeLinkNode *preNode = NULL;
        while (lastHead != NULL) {
            //traversing level i to populate next pointer in level i+1
            TreeLinkNode *lastCur = lastHead;
            while (lastCur != NULL) {
                if (lastCur->left != NULL) {
                    if (curHead == NULL) { //first node in level i+1
                        curHead = lastCur->left;
                        preNode = curHead;
                    } else {
                        preNode->next = lastCur->left;
                        preNode = preNode->next;
                    }
                }
                if (lastCur->right != NULL) {
                    if (curHead == NULL) { //first node in level i+1
                        curHead = lastCur->right;
                        preNode = curHead;
                    } else {
                        preNode->next = lastCur->right;
                        preNode = preNode->next;
                    }
                }
                //update lastCur
                lastCur = lastCur->next;
            }
            //update lastHead to level i+1
            lastHead = curHead;
            curHead = NULL;
        }
    }
};
