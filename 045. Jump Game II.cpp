/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.
*/

/*
Analysis: It is very clear that this is DP problem. We need to keep track of the minimum number of steps to reach every index as well as the maximally reachable index at every given point.

Time: O(n), Space: O(n).
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size(), maxIndex = 0;
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            if (i + nums[i] <= maxIndex) continue;
            for (int j = maxIndex+1; j <= min(i+nums[i], n-1); j++) dp[j] = dp[i] + 1;
            maxIndex = i + nums[i];
        }
        
        return dp[n-1];
    }
};
