/*
Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums being 2.

Hint:

Try two pointers.
Did you use the property of "the order of elements can be changed"?
What happens when the elements to remove are rare?
*/

/*
This problem is exactly the same as Problem 26 (https://leetcode.com/problems/remove-duplicates-from-sorted-array/?tab=Description). See my solution here: https://github.com/Hangjun/MyLeetCode/blob/master/026.%20Remove%20Duplicates%20from%20Sorted%20Array.cpp.

Time: O(n), Space: O(1).
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) return 0;
        int len = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) nums[++len] = nums[i];
        }
        return len+1;
    }
};

