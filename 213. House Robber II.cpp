/*
Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

/*
Analysis: This problem is a little tricky at first glance. However, if you have finished the House Robber problem, this problem can simply be decomposed into two House Robber problems.
Suppose there are n houses, since house 0 and n - 1 are now neighbors, we cannot rob them together and thus the solution is now the maximum of

Rob houses 0 to n - 2;
Rob houses 1 to n - 1.
*/

// Time: O(n), Space: O(1)
class Solution {
public:
    int rob(vector<int> &nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        return max(robNoncircular(nums, 0, n-2), robNoncircular(nums, 1, n-1));
    }
    
private:
    int robNoncircular(vector<int> &nums, int start, int end) {
        int a = 0, b = 0;
        for (int i = start; i <= end; i++) {
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
