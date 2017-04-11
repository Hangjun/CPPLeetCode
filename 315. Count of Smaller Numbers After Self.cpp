/*
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/

// BST solution. Time: O(nlogn), Space: O(n).
class TreeCountNode {
public:
    int val;
    TreeCountNode *left;
    TreeCountNode *right;
    int count;
    
    TreeCountNode(int x) : val(x), left(NULL), right(NULL) {
        count = 0;
    }
};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res;
        if (nums.empty()) return res;
        if (nums.size() == 1) return vector<int>(1, 0);
        TreeCountNode *root = new TreeCountNode(nums.back());
        res.push_back(0);
        for(int i = nums.size()-2; i >= 0; i--) {
            TreeCountNode *curNode = root;
            int count = 0;
            // find nums[i] in the BST
            while (true) {
                if (nums[i] <= curNode->val) {
                    curNode->count++;
                    if (!curNode->left) {
                        curNode->left = new TreeCountNode(nums[i]);
                        break;
                    }
                    curNode = curNode->left;
                } else {
                    count += curNode->count+1;
                    if (!curNode->right) {
                        curNode->right = new TreeCountNode(nums[i]);
                        break;
                    }
                    curNode = curNode->right;
                }
            }
            
            res.push_back(count);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
