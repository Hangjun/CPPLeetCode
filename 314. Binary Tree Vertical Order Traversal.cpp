/*
Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples:

Given binary tree [3,9,20,null,null,15,7],
   3
  /\
 /  \
 9  20
    /\
   /  \
  15   7
return its vertical order traversal as:
[
  [9],
  [3,15],
  [20],
  [7]
]
Given binary tree [3,9,8,4,0,1,7],
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
return its vertical order traversal as:
[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2
return its vertical order traversal as:
[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]
*/

/*
Analysis: The first tempting idea is to use DFS:
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
    unordered_map<int, vector<int>> ht;
    
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        int curLevel = 0;
        int minLevel = 0, maxLevel = 0;
        helper(root, curLevel, minLevel, maxLevel);
        for (int i = minLevel; i <= maxLevel; i++) {
            res.push_back(ht[i]);
        }
        return res;
    }
    
    void helper(TreeNode *curNode, int curLevel, int &minLevel, int &maxLevel) {
        if (!curNode) return;
        ht[curLevel].push_back(curNode->val);
        minLevel = min(minLevel, curLevel);
        maxLevel = max(maxLevel, curLevel);
        if (curNode->left) helper(curNode->left, curLevel-1, minLevel, maxLevel);
        if (curNode->right) helper(curNode->right, curLevel+1, minLevel, maxLevel);
    }
};

/*
However, this is the wrong answer. It does not guarrantee that the nodes on the same level are printed out top-to-bottom as in the original order in the tree. Imagine a tree with a large left substree. The nodes in the left subtree will be included in the vector earlier than the right substree nodes. 

On a second thought, we should be using BFS instead of DFS precisely for this reason.
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
    unordered_map<int, vector<int>> ht;
    int minLevel = 0, maxLevel = 0;
    
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        findMinMaxLevel(root, 0);
        queue<pair<TreeNode *, int>> q;
        q.push(make_pair(root, 0));
        
        while (!q.empty()) {
            TreeNode *curNode = q.front().first;
            int curLevel = q.front().second;
            q.pop();
            ht[curLevel].push_back(curNode->val);
            if (curNode->left) q.push(make_pair(curNode->left, curLevel-1));
            if (curNode->right) q.push(make_pair(curNode->right, curLevel+1));
        }
        
        for (int i = minLevel; i <= maxLevel; i++) res.push_back(ht[i]);
        
        return res;
    }
    
    void findMinMaxLevel(TreeNode *curNode, int curLevel) {
        if (!curNode) return;
        minLevel = min(minLevel, curLevel);
        maxLevel = max(maxLevel, curLevel);
        if (curNode->left) findMinMaxLevel(curNode->left, curLevel-1);
        if (curNode->right) findMinMaxLevel(curNode->right, curLevel+1);
    }
};
