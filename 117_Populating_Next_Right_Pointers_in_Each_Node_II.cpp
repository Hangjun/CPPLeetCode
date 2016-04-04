/*
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

    You may only use constant extra space.

For example,
Given the following binary tree,

         1
       /  \
      2    3
     / \    \
    4   5    7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/

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
