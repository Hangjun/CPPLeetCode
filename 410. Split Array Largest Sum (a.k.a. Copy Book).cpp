/*
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
*/

/*
Analysis: This is exactly the famous (notorious) Copy Book problem (http://www.lintcode.com/en/problem/copy-books/).

The non-dp solution should be straightforward. The maximum possible answer is the total sum, the minimum possible answer if the largest element. Then we binary search. For each value mid, we traverse the array and partition in a greedy fashion - as long as we can still fit more (i.e. total sum is <= mid) we add the current element into the current partition.

Remark: This solution is very similar to the binary search solution to Problem 209. Minimum Size Subarray Sum (https://leetcode.com/problems/minimum-size-subarray-sum/#/description). 

Caution: We can do this also because the elements in the array are non-negative. For arbitrary numbers, we cannot use greedy algorithm. In that case, DP is necessary.

Whenever we are looking for a minimum sized solution, try binary search.

Time: O(nlog(total sum - max element)), n = nums.size(); Space: O(1).
*/
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        long left = INT_MIN;
        long right = 0;
        for (int n : nums) {
            left = max(left, (long)n);
            right += n;
        }
        if (m == 1) return right;
        
        while (left <= right) {
            long mid = left + (right-left)/2;
            if (validPartition(nums, mid, m)) right = mid-1;
            else left = mid+1;
        }
        
        return left;
    }
    
    bool validPartition(vector<int> &nums, int sum, int m) {
        int curSum = 0;
        int count = 1;
        for (int n : nums) {
            curSum += n;
            if (curSum > sum) {
                curSum = n;
                if (++count > m) return false;
            }
        }
        return true;
    }
};

// A slow but very beautiful DP solution. Time: O(n^2 m), Space: O(nm).
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<long> partialSum(n, 0);
        vector<vector<long>> dp(n, vector<long>(m+1, INT_MAX)); // dp[i][k] = max sum with k partitions on nums[0:i]
        // generic state transfer function: dp[i][k] = min(dp[i][k], max(partialSum[j:i], dp[j-1][k-1])), for all k-1 <= j <= i
        
        for (int i = 0; i < n; i++) partialSum[i] = i == 0 ? nums[0] : (nums[i] + partialSum[i-1]);
        
        for (int i = 0; i < n; i++) {
            int maxPartition = min(m, i+1); // [0:i] can have at most i+1 partitions
            for (int k = 1; k <= maxPartition; k++) {
                if (k == 1) {
                    dp[i][k] = partialSum[i];
                    continue;
                }
                for (int j = i; j >= k-1; j--) { // [0:j-1] with k-1 partitions and a single partition [j: i] 
                    long partial = partialSum[i]-partialSum[j]+nums[j];
                    if (partial > dp[i][k]) continue; // in case there is negative number: need to look all j
                    dp[i][k] = min(dp[i][k], max(partial, dp[j-1][k-1]));
                }
            }
        }
        
        return dp[n-1][m];
        
    }
};

/*
There exsits a O(nm) time solution.
*/
