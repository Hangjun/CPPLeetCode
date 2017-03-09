/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.

*/

/* Analysis:
The idea is to sort the array and do a linear scan. This takes O(nlogn) time:
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-1; i++) {
            if (nums[i] == nums[i+1]) {
                return nums[i];
            }
        }
    }
};

/* Analysis:
This problem also has a very interesting solution using binary search. One natural idea is to binary search the given array to find the 
duplicate. After some thought we see that this is not possible, since if the duplicating number are in two seperate subarrays in the first 
place, then we would never be able to find it. The key giveaway is the 4th requirement given above: "There is only one duplicate number in 
the array, but it could be repeated more than once." This suggests that we should perform binary search on the RANGE [1,n]. 

We repeatedly divide the possible range [1,n] into two pieces: [left, mid] and [mid+1, right]. The key observation is that, if there are no 
duplicate, then there should be exactly mid - left + 1 many elements within the first range, and right-mid many element in the second range. 
Thus if there are more elements than desired, we know that there is a duplicate in that range. It is the range that we subdividing!

Time: O(nlogn), Space: O(1).
*/

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

// Or more concicsely:
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 1, right = nums.size()-1;
        // loop invariant: duplicate is contained within [left, right] range
        while (left < right) {
            int mid = left + (right-left)/2;
            int count = 0;
            for (auto n : nums) {
                if (n >= left && n <= mid) count++;
            }
            if (count > mid - left + 1) right = mid;
            else left = mid+1;
        }
        return left;
    }
};

/* There is actually a very neat O(n) time O(1) space solution using the idea of cycle detection in a linked list: https://discuss.leetcode.com/topic/25913/my-easy-understood-solution-with-o-n-time-and-o-1-space-without-modifying-the-array-with-clear-explanation/20. This solution is not the algorithm this problem is looking for, so we won't spend the time to further understand it.
*/
