/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
*/

/*
Analysis: The array is sorted. This means that all duplicates are consecutive. One naive algorithm is to scan the array front to back, once a duplicate is identified, copy the rest of the array forward. This runs in O(n^2) time. Note that this problem only requires us to return the adjusted length of the array, and we can modify the content of the array. This leads to the following algorithm which simply overwrites a duplicate with non-duplicate entries instead of sliding them to the front.

Time: O(n), Space: O(1). 1 Pass.
*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int len = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[len]) nums[++len] = nums[i];
        }
        return len+1;
    }
};
