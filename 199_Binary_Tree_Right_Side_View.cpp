/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---

You should return [1, 3, 4]. 
*/


// A straightfoward solution is to use BFS to scan each level, and fetch the right most node from each level:
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
    vector<int> rightSideView(TreeNode* root) {
        // first do a level order reverseal, then scan each leve, return the right most node
        vector<int> rightSideNode;
        vector<vector<int>> levels = levelOrder(root);
        for (int i = 0; i < levels.size(); i++) {
            rightSideNode.push_back(levels[i].back());
        }
        return rightSideNode;
    }
    
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode *> curLevel;
        queue<TreeNode *> nextLevel;
        curLevel.push(root);
        while (!curLevel.empty()) {
            vector<int> curLevelVal;
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevelVal.push_back(curNode->val);
                if (curNode->left)
                    nextLevel.push(curNode->left);
                if (curNode->right)
                    nextLevel.push(curNode->right);
                curLevel.pop();
            }
            result.push_back(curLevelVal);
            swap(curLevel, nextLevel);
        }
        return result;
    }
};


// A much cleaner solution is to use DFS and directly fetches the right most node from each level in a mid-right-left traverse order:
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        rightSideViewDFS(root, 1, res);
        return res;
    }
    
    void rightSideViewDFS(TreeNode *curNode, int level, vector<int> &res) {
        if (level > res.size()) res.push_back(curNode->val);
        if (curNode->right) rightSideViewDFS(curNode->right, level+1, res);
        if (curNode->left) rightSideViewDFS(curNode->left, level+1, res);
    }
};

/* Analysis:
The traverse order is mid-right-left. The level variable keeps track of the current level we are current in. The idea is that "if (level > res.size())", the either the current node is the right most node of this level (following the curNode->right branch) that hasn't been included yet, or this current node, following the curNode->left branch, is a left child, however, its right sibling does not exist. In either case, we should include this node.

The key is, we should include a node at EVERY level. The mid-right-left traverse guarantees that the current node must be the right most if if (level > res.size()).
*/
