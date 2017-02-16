/*
Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,
   1
    \
     3
    / \
   2   4
        \
         5
Longest consecutive sequence path is 3-4-5, so return 3.
   2
    \
     3
    / 
   2    
  / 
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
*/

/* 
It is immediately noticed that this is the same as the ski problem. The only difference is that the sequence must be consecutive.
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
    int longestConsecutive(TreeNode* root) {
        if (!root) return 0;
        unordered_map<TreeNode *, int> dp; // node->longest path from this node initially
        int maxLen = 0;
        
        TreeNode *curNode = root;
        stack<TreeNode *> st;
        while (curNode || !st.empty()) {
            if (curNode) {
                st.push(curNode);
                curNode = curNode->left;
            } else {
                TreeNode *readyNode = st.top();
                st.pop();
                maxLen = max(maxLen, dfs(readyNode, dp));
                curNode = readyNode->right;
            }
        }
        
        return maxLen;
    }
    
    int dfs(TreeNode *root, unordered_map<TreeNode *, int> &dp) {
        if (dp.find(root) != dp.end()) return dp[root];
        dp[root] = 0;
        if (root->left && root->left->val == root->val + 1) dp[root] = max(dp[root], dfs(root->left, dp));
        if (root->right && root->right->val == root->val + 1) dp[root] = max(dp[root], dfs(root->right, dp));
        
        return ++dp[root];
    }
};

// With the special tree structure, this problem actually can be solved in a much simpler DFS:
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
    int longestConsecutive(TreeNode* root) {
        return longestConsecutiveRecur(root, NULL, 0);
    }
    
    int longestConsecutiveRecur(TreeNode *curNode, TreeNode *parentNode, int len) {
        if (!curNode) return len;
        len = (parentNode && curNode->val == parentNode->val+1) ? len+1 : 1;
        return max(len, max(longestConsecutiveRecur(curNode->left, curNode, len), longestConsecutiveRecur(curNode->right, curNode, len)));
    }
};


/* 

Analysis:

The reason that we have this simpler DFS solution is that this problem is slightly different from the ski problem in that the path has to be a parent->child path. Therefore, for a given node, we can compute the longest increasing consecutive sequence that reaches it. In the ski problem, also the first solution, we were computing the longest paths eminating from the current node.

We now present an iterative solution that sequentially traverses the tree top-to-bottom level by level, and computes the above "terminating optimal value" for every node.

Time: O(n), Space: O(n)
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
    int longestConsecutive(TreeNode* root) {
        if (!root) return 0;
        int maxLen = 0;
        queue<pair<TreeNode *, int>> q;
        q.push(pair<TreeNode *, int>(root, 1));
        
        while (!q.empty()) {
            pair<TreeNode *, int> p = q.front();
            q.pop();
            TreeNode *curNode = p.first;
            int curLen = p.second;
            maxLen = max(maxLen, curLen);
            if (curNode->left) {
                if (curNode->left->val == curNode->val+1)
                    q.push(pair<TreeNode *, int>(curNode->left, curLen+1));
                else
                    q.push(pair<TreeNode *, int>(curNode->left, 1));
            }
            if (curNode->right) {
                if (curNode->right->val == curNode->val+1)
                    q.push(pair<TreeNode *, int>(curNode->right, curLen+1));
                else
                    q.push(pair<TreeNode *, int>(curNode->right, 1));
            }
        }
        
        return maxLen;
    }
};

/* Key: The tree structure (there is a unique path from root to any node) allows us to compute terminating optimal value as opposed to eminating optimal value, and trust it that it's indeed the optmial.
*/
