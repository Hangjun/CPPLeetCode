/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.

*/

// Submission #1: Accepted.

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // all numbers are within [left, right] = [1,n]
        int left = 1;
        int right = nums.size()-1;
        // loop-invariant: duplicate is contained withtin [left, right], inclusive
        while (left < right) {
            int mid = left + (right - left)/2;
            if (containsDup(nums, left, mid)) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
        return left;
    }
    
private:
    bool containsDup(vector<int> &nums, int lb, int up) {
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] >= lb && nums[i] <= up) {
                count++;
            }
        }
        return (count > up - lb + 1) ? true : false;
    }
};
