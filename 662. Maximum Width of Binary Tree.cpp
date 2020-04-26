/*
Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum width among all levels. The binary tree has the same structure as a full binary tree, but some nodes are null.

The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).

Note: Answer will in the range of 32-bit signed integer.

/*
Solution: We use level order traversal and we keep track of the indices for each level. Since the input binary tree is complete, we can think of it as an array in which the left and right child of the ith node is 2i and 2i + 1, respectively.
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
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode *> level;
        queue<int> indices;
        int res = 1;
        
        level.push(root);
        indices.push(0);
        
        while (!level.empty()) {
            int curLevelSize = level.size();
            int left = 0, right = 0;
            for (int i = 0; i < curLevelSize; i++) {
                TreeNode *curNode = level.front();
                level.pop();
                int curIndex = indices.front();
                indices.pop();
                
                if (i == 0) left = curIndex;
                if (i == curLevelSize-1) right = curIndex;
                
                if (curNode->left) {
                    level.push(curNode->left);
                    indices.push(2 * curIndex);
                }
                
                if (curNode->right) {
                    level.push(curNode->right);
                    indices.push(2 * curIndex + 1);
                }
            }
            
            res = max(res, right - left + 1);
        }
        
        return res;
    }
};
