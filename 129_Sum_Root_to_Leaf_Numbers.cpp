/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25. 
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
    int sumNumbers(TreeNode* root) {
       int curNum = 0;
       int sum = 0;
       return sumNumbersDFS(root, curNum, sum);
    }
    
    /*  the global quantity sum must be passed as a reference
        the local quantity is not a reference, thus we do not need
        to reset it when we return from a path search
    */
    int sumNumbersDFS(TreeNode *root, int curNum, int &sum) {
        if (!root) return 0;
        curNum = curNum*10 + root->val;
        if (root->left == NULL && root->right == NULL) {
            //we have reached the end of a path
            sum += curNum;
        } else {
            sumNumbersDFS(root->left, curNum, sum);
            sumNumbersDFS(root->right, curNum, sum);
        }
        return sum;
    }
};

// Another DFS solution in which at the beginning of each recursion, curSum = current sum including the current node's value.
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
    int sumNumbers(TreeNode* root) {
        if (!root) return 0;
        int sum = 0;
        int curSum = root->val;
        sumNumbersDFS(root, curSum, sum);
        return sum;
    }
    
    void sumNumbersDFS(TreeNode *curNode, int curSum, int &sum) {
        if (curNode->left == NULL && curNode->right == NULL) {
            sum += curSum;
            return;
        }
        if (curNode->left) sumNumbersDFS(curNode->left, curSum * 10 + curNode->left->val, sum);
        if (curNode->right) sumNumbersDFS(curNode->right, curSum * 10 + curNode->right->val, sum);
    }
};
