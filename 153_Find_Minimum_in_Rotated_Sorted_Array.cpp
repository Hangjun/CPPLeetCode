/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) { // nums[mid,...,right] is sorted
                right = mid;
            } else { // min exists in nums[mid+1,...,right]
                left = mid+1;
            }
        }
        return nums[left];
    }
};
