/*
Total Accepted: 1151
Total Submissions: 2127
Difficulty: Easy
Contributors:
love_Fawn
You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.
*/

/*
Analysis: This is the reverse problem of Problem 536. Construct Binary Tree from String (https://leetcode.com/problems/construct-binary-tree-from-string/#/description). Anything construction that is built out of any order of traversal of the tree can often be solved via recursion.
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
    string tree2str(TreeNode* t) {
        if (!t) return "";
        string cur = to_string(t->val);
        
        if (t->left) cur += '(' + tree2str(t->left) + ')';
        else if (t->right) cur += "()"; // caution: we do not omit the first parenthesis pair even if it is empty to maintain consistency
        
        if (t->right) cur += '(' + tree2str(t->right) + ')';
        
        return cur;
    }
};

// Or for those that like one-liners:
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
    string tree2str(TreeNode* t) {
        return !t ? "" : to_string(t->val) + (!t->left && !t->right ? "" : "(" + tree2str(t->left) + ")" + (!t->right ? "" : "(" + tree2str(t->right) + ")"));
    }
};
