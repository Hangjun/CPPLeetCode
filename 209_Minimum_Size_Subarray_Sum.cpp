/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
*/

// Two pointer sliding window. Time: O(n), Space: O(1).
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n <= 0 || s <= 0) return 0;
        int left = 0, right = -1, minLen = n+1;
        int sum = 0;
        while (right < n) {
            while (right < n && sum < s)
                sum += nums[++right];
            if (sum >= s) {
                minLen = min(minLen, right-left+1);
                sum -= nums[left++];
            }
        }
        
        return minLen == n+1? 0 : minLen;
    }
};

// Binary search the window size. Time: O(nlogn), Space: O(1).



