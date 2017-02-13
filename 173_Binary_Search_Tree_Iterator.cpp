/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        curNode = root;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return curNode || !st.empty();
    }

    /** @return the next smallest number */
    int next() {
        while (curNode || !st.empty()) {
            st.push(curNode);
            curNode = curNode->left;
        }
        TreeNode *readyNode = st.top();
        st.pop();
        curNode = readyNode->right; 
        return readyNode->val;
    }

private:
    stack<TreeNode *> st;
    TreeNode *curNode;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
 
