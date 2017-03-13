/*
Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
Given nums = [-2, -1, 2, 1], k = 1,
return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

Follow Up:
Can you do it in O(n) time?
*/

/*
Analysis: The key to solving this problem is to realize that we need to access information about nums[i:j], the sum of all numbers from nums[i] to nums[j]. This immediately suggests that we should use partial sums. Given ps[j], the sum of nums[0] to nums[j], we can traverse numbers before j, and if the ps[j]-ps[i] == k, we return the subarray nums[i+1:j]. 

We can improve this by using a hash table that maps subarray partial ps[i] to i. One thing we need to caution is that, there might be multiple ps[i]'s with the same value. We need to make sure to only record the first one as we are computing the maximum sized subarray. Morever, we do not need to precompute the partial sum array. We only need to have use a curSum that computes the current sum from nums[0] to nums[i]. This saves us O(n) space.

Time: O(n), Space: O(n).
*/
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        int curSum = 0;
        int maxLen = 0;
        unordered_map<int, int> ht;
        for (int i = 0; i < nums.size(); i++) {
            curSum += nums[i];
            if (curSum == k) {
                maxLen = i+1;
            } else if (ht.find(curSum-k) != ht.end()) {
                maxLen = max(maxLen, i-ht[curSum-k]);
            }
            if (ht.find(curSum) == ht.end()) ht[curSum] = i;
        }
        return maxLen;
    }
};
