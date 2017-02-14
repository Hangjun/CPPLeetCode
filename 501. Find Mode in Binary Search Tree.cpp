/*
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
For example:
Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
*/

// Time O(n), Space O(n). DFS to find frequency counts of all node values.
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
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        unordered_map<int, int> map; // node value -> frequency count
        int modeCount = findModeCountDFS(root, map);
        
        for (auto p : map) {
            if (p.second == modeCount) res.push_back(p.first);
        }
        
        return res;
    }
    
    int findModeCountDFS(TreeNode *curNode, unordered_map<int, int> &map) {
        if (!curNode) return 0;
        if (map.find(curNode->val) == map.end()) {
            map[curNode->val] = 1;
        } else {
            map[curNode->val]++;
        }
        
        return max(map[curNode->val], max(findModeCountDFS(curNode->left, map), findModeCountDFS(curNode->right, map)));
    } 
};


/* The above solution uses O(n) space. Can we use O(1) space except the space used in recursion? The idea is to inorder traverse the tree while keeping track of the longest mode values.

We can use Morris traversal to reduce the space complexity to absolutely O(1), but that does not bring any incremental algorithmic beauty to the problem.
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
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        int curCount = 0, maxCount = 0, curVal = 0;
        findModeRecur(root, curVal, curCount, maxCount, res);
        return res;
    }
    
    void findModeRecur(TreeNode *curNode, int &curVal, int &curCount, int &maxCount, vector<int> &res) {
        if (!curNode) return;
        findModeRecur(curNode->left, curVal, curCount, maxCount, res);
        
        if (!curCount || curVal != curNode->val) {
            curVal = curNode->val;
            curCount = 1;
        } else {
            curCount++;
        }
        
        if (curCount > maxCount) {
            maxCount = curCount;
            res.clear();
            res.push_back(curVal);
        } else if (curCount == maxCount) {
            res.push_back(curVal);
        }
        
        findModeRecur(curNode->right, curVal, curCount, maxCount, res);
    }
};
