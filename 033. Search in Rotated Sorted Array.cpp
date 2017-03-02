/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/

// Time: O(logn), Space: O(1).
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = left + (right - left)/2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < nums[right]) { // nums[mid], ..., nums[right] is sorted
                if (target > nums[mid] && target <= nums[right])
                    left = mid+1;
                else 
                    right = mid-1;
            } else { // nums[left], ..., nums[mid] is sorted
                if (target < nums[mid] && target >= nums[left]) 
                    right = mid-1;
                else
                    left = mid+1;
            }
        }
        return -1;
    }
};
