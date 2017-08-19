/*
Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
Note:
1 <= k <= n <= 30,000.
Elements of the given array will be in the range [-10,000, 10,000].
*/

/*
Solution: Very straightforward sliding window idea. 

Time: O(n), Space: O(1).
*/
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        const int n = nums.size();
        long long sum = 0;
        // warm up with the first width k window
        for (int i = 0; i < min(k, n); i++) sum += nums[i];
        
        double res = sum / (double) min(k, n);
        if (n <= k) return res;
        
        for (int i = k; i < n; i++) {
            // kick the first element from sum; recompute average
            sum -= nums[i-k];
            sum += nums[i];
            res = max(res, sum / (double) k);
        }
        
        return res;
    }
};
