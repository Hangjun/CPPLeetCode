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
Analysis: The non-dp solution should be straightforward. The maximum possible answer is the total sum, the minimum possible answer if the largest element. Then we binary search. For each value mid, we traverse the array and partition in a greedy fashion - as long as we can still fit more (i.e. total sum is <= mid) we add the current element into the current partition.

Remark: This solution is very similar to the binary search solution to Problem 209. Minimum Size Subarray Sum (https://leetcode.com/problems/minimum-size-subarray-sum/#/description). 

Whenever we are looking for a minimum sized solution, try binary search.

Time: O(n^2), n = nums.size(); Space: O(1).
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
