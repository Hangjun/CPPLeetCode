/*
Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].
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

/*
Solution: The first idea is to construct the max tree recursively. What we were doing was, given that a root is found, we want to know the maximum to its left. and to its right. This reminds us of problems like Trapping Water and Container with Most Water. 

Often times when we want to find the max/min to the left or right of a given node, a stack can be used:

Time: O(n), Space: O(n).
*/
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode *root = NULL;
        if (nums.empty()) return root;
        stack<TreeNode *> st;
        for (int i = 0; i < nums.size(); i++) {
            TreeNode *curNode = new TreeNode(nums[i]);
            
            // find the left child from the stack
            while (!st.empty() && curNode->val > st.top()->val) {
                curNode->left = st.top();
                st.pop();
            }
            
            // curNode is the right child of the top node of the stack, if exists
            if (!st.empty()) {
                st.top()->right = curNode;
            }
            st.push(curNode);
        }
        
        // the bottom node of the stack is the root
        while (!st.empty()) {
            root = st.top();
            st.pop();
        }
        
        return root;        
    }
};

/*
Analysis: Changing curNode->val > (nodes.top())->val to curNode->val < (nodes.top())->val will generate a min tree. 

We point out an interesting fact: the max tree we constructed from an input array satisfies two properties:
1. The max tree is a binary heap;
2. Inorder traversal of the max tree recovers the input array.

We say that a tree constructed from an input array satisfying the above two properties (called the heap property and the 
symmetric Inorder Traversal property, respectively) a Cartesian Tree. 
Details see https://en.wikipedia.org/wiki/Cartesian_tree.

Why do we care about max/min trees? Besides from the fact that they can be used for range search in computational geometry, 
they are also connected to the expression trees discussed above. Recall that, to build an expression tree from its infix 
expression, we first converted the expression to postfix, then build the tree. Can we directly build the expression? Note that 
in an expression tree, the leaves are all operands, and internal nodes are all operators. The root node is the least priority 
operator. Therefore, we can assign weights to the operators and operands, where operators get the maximum weights, and higher 
priority operator get higher weights. Then the min tree associated with this array of weights correspond exactly to the 
expression tree. This approach is documented above in LintCode Problem 367: Expression Tree Build.

*/
