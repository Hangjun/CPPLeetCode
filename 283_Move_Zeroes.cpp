/*
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:

    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/

/* Solution: Two Pointers
Time: O(n)
Space: O(1)
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if (nums.empty()) return;
        int left = 0, right = 0;
        // invariant: nums[0,...,left-1] contains only nonzeros
        // nums[left,...,right-1] contains only zeros
        // when right == nums.size() the requirement is then met
        while (right < nums.size()) {
            if (nums[right] != 0) {
                swap(nums[left++], nums[right++]);
            } else {
                right++;
            }
        }
    }
};
