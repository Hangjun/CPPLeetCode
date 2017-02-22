/*
Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        unordered_map<int, int> ht; // subtree sum -> frequency
        int maxCount = 1;
        findFrequentTreeSumDFS(root, ht, maxCount);
        
        for (auto t : ht) {
            if (t.second == maxCount) res.push_back(t.first);
        }
        
        return res;    
    }
    
    int findFrequentTreeSumDFS(TreeNode *curNode, unordered_map<int, int> &ht, int &maxCount) {
        int sum = 0;
        if (!curNode) return sum;
        sum = curNode->val;
        sum += findFrequentTreeSumDFS(curNode->left, ht, maxCount);
        sum += findFrequentTreeSumDFS(curNode->right, ht, maxCount);
        
        ht[sum]++;
        maxCount = max(maxCount, ht[sum]);
        return sum;
    }
    
};

/* 
Remark: this is essentially the same problem as Problem 501 (https://github.com/Hangjun/MyLeetCode/blob/master/501.%20Find%20Mode%20in%20Binary%20Search%20Tree.cpp)
*/
