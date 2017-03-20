/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

click to show spoilers.

Note:
Your solution should be in logarithmic complexity.
*/

/*
Analysis: It is clear that this is a binary search problem. Therefore the key is to define the loop invariant in terms of left and right. The tricky part here is that the split condition is not defined by comparing mid with left or right, but with its neighbor mid+1.

Time: O(logn), Space: O(1).
*/
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        // loop invariant: peak is contained in [left, right]
        while (left < right) {
            int mid = left + (right - left)/2;
            if (nums[mid] < nums[mid+1]) left = mid+1;
            else right = mid;
        }
        return left;
    }
};
