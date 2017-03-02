/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.
*/

//Time: O(n) worst case, Space: O(1)
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = left + (right - left)/2;
            if (nums[mid] == target) return true;
            if (nums[mid] < nums[right]) { // nums[mid], ..., nums[right] is sorted
                if (target > nums[mid] && target <= nums[right])
                    left = mid+1;
                else 
                    right = mid-1;
            } else if (nums[mid] > nums[right]) { // nums[left], ..., nums[mid] is sorted
                if (target < nums[mid] && target >= nums[left]) 
                    right = mid-1;
                else
                    left = mid+1;
            } else if (nums[mid] == nums[left]) {
                left++;
            } else { // nums[mid] == nums[right]
                right--;
            }
        }
        return false;
    }
};
