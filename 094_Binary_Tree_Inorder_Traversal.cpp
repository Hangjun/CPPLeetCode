/*
Given a binary tree, return the inorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,3,2].
Note: Recursive solution is trivial, could you do it iteratively?
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
    vector<int> inorderTraversal(TreeNode* root) {
        // left-mid-right
        vector<int> res;
        if (!root) return res;
        stack<TreeNode *> st;
        TreeNode *curNode = root;
        while (curNode || !st.empty()) {
            if (curNode) {
                st.push(curNode);
                curNode = curNode->left;
            } else { // curNode == NULL, backtrack
                TreeNode *tmpNode = st.top();
                st.pop();
                res.push_back(tmpNode->val);
                curNode = tmpNode->right;
            }
        }
        return res;
    }
};

/* Morris traversal solution: O(n) time, O(1) space */
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodeValues;
        if (root == NULL) return nodeValues;
        TreeNode *curNode, *preNode;
        curNode = root;
        while (curNode != NULL) {
            //check if it is the leftmost
            if (curNode->left == NULL) {
                nodeValues.push_back(curNode->val);
                curNode = curNode->right;
            } else {
                preNode = curNode->left;
                //find the predecesor of curNode by walking preNode to its rightmost
                while(preNode->right != NULL && preNode->right != curNode)
                    preNode = preNode->right;
                if (preNode->right == NULL) {
                    //link preNode back to curNode
                    preNode->right = curNode;
                    curNode = curNode->left;
                } else { //preNode is already linked to curNode, reset this link to NULL
                    preNode->right = NULL;
                    nodeValues.push_back(curNode->val);
                    curNode = curNode->right;
                }
            }
        }
        return nodeValues;
    }
};
