/*
You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   
Note:
There will only be '(', ')', '-' and '0' ~ '9' in the input string.
An empty tree is represented by "" instead of "()".
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
    TreeNode* str2tree(string s) {
       int i = 0;
       return s.empty() ? NULL : build(s, i);
    }

private:
    TreeNode* build(string& s, int& i) {
        int start = i;
        bool neg = false;
        if (s[i] == '-') {
            neg = true;
            i++;
        }
        int label = 0;
        while (isdigit(s[i])) {
            label = label * 10 + (s[i] - '0');
            i++;
        }
        if (neg) label = -label;
        TreeNode *curNode = new TreeNode(label);
        if (s[i] == '(') {
            curNode->left = build(s, ++i);
            i++; // move pass the corresponding ')'
        }
        if (s[i] == '(') { // meet '(' the second time
            curNode->right = build(s, ++i);
            i++;
        }
        
        return curNode;
    }
};
