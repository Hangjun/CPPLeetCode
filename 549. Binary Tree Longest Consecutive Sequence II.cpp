/*
Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.

Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.

Example 1:
Input:
        1
       / \
      2   3
Output: 2
Explanation: The longest consecutive path is [1, 2] or [2, 1].
Example 2:
Input:
        2
       / \
      1   3
Output: 3
Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
Note: All the values of tree nodes are in the range of [-1e7, 1e7].
*/

/*
Analysis: In part I of this problem, we only needed to keep track of a single length variable as all paths are eminating from the root. Now, not only can the paths start from any node, but the values can be either increasing or decreasing as well. Therefore when we traverse recursively, we must be carrying two variables: one indicating the the maximum increasing path length from this node, and the other the maximum decresing path length from this node. 

Now the question is how we should traverse. In part I, we traversed via DFS since all paths are root-to-node paths. In the current more general setting, we need to compute the maximum increasing/decreasing length of paths starting from any node. Therefore, at a node, we need to know these information from the left and from the right before deciding which route to take. This suggests using postorder traversal.
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
    int maxLen = 0;
    
    int longestConsecutive(TreeNode* root) {
        traverse(root);
        return maxLen;
    }
    
    pair<int, int> traverse(TreeNode *curNode) {
        if (!curNode) return make_pair(0, 0);
        int inc = 1, dec = 1; // increase and decrease lengths respectively
        if (curNode->left) {
            pair<int, int> pLeft = traverse(curNode->left);
            if (curNode->val == curNode->left->val + 1) dec = pLeft.second + 1;
            else if (curNode->val == curNode->left->val - 1) inc = pLeft.first + 1;
        }
        
        if (curNode->right) {
            pair<int, int> pRight = traverse(curNode->right);
            if (curNode->val == curNode->right->val + 1) dec = max(dec, pRight.second + 1);
            if (curNode->val == curNode->right->val - 1) inc = max(inc, pRight.first + 1);
        }
        
        maxLen = max(maxLen, inc + dec - 1);
        return make_pair(inc, dec);
    }
};
