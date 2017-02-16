/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n^2) complexity.

Follow up: Could you improve it to O(n log n) time complexity? 
*/

/* Solution #1: Dynamic Programming
Time: O(n^2)
Space: O(n)
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty())  return 0;
        int n = nums.size();
        // dp[i] = length of LIS ending at nums[i]
        vector<int> dp (n, 1);
        int maxLen = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], 1+dp[j]);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
};


/* Solution #2: Monotonic Array
Time: O(nlogn): logn to compute the lower_bound using binary search
Space: O(n)
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> v;
        v.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > v.back()) {
                v.push_back(nums[i]);
                continue;
            }
            // v[j] = first elem that is NOT < than nums[i]
            int j = lower_bound(v.begin(), v.end(), nums[i]) - v.begin();
            v[j] = nums[i];
        }
        return v.size();
    }
};
