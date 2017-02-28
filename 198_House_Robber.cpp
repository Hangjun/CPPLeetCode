/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// Time: O(n), Space: O(n)
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        if (n == 1) return nums[0];
        vector<int> dp(n, 0); // dp[i] = amount of money up to the ith house such that the ith house must be robbed
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
        }
        return dp[n-1];
    }
};

// We can improve the space complexity to O(1) using the rolling array trick:
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        if (n == 1) return nums[0];
        vector<int> dp(2, 0); // dp[i] = amount of money up to the ith house such that the ith house must be robbed
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i%2] = max(dp[(i-2)%2] + nums[i], dp[(i-1)%2]);
        }
        return dp[(n-1)%2];
    }
};

// More directly:
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        int a = 0, b = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2) {
                a += nums[i];
                a = max(a, b);
            } else {
                b += nums[i];
                b = max(a, b);
            }
        }
        return max(a, b);
    }
};
