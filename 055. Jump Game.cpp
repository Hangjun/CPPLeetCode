/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/

/*
Analysis: This is a very interesting problem. The point is that each entry in the array stores the maximum number of steps we can jump from there. We do not have to jump that much. It is only the maximally allowed jump length. Therefore we use greedy algorithm to solve it.

Time: O(n), Space: O(1).
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int maxIndex = 0; // the maximal index that we can jump to
        
        for (int i = 0; i < n; i++) {
            if (i > maxIndex || maxIndex >= n-1) break;
            maxIndex = max(maxIndex, i + nums[i]);
        }
        
        return maxIndex >= n-1;
    }
};
