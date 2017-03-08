/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/

/*
Analysis: This is a classic "two" pointer + pivot = partition problem. Since there are three colors, we use thre pointers left, cur and right. We maintain the loop invariant such that [0, left) contains only 0's, [left, cur) contains only 1's, and (right, nums.size()) contains only 2's. The unknown range is [cur, right]. As cur traverses up to right, we know the desired sorting is complete.

Time: O(n), Space: O(1). 1 Pass.
*/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.empty()) return;
        int left = 0, right = nums.size()-1;
        int cur = 0;
        while (cur <= right) {
            if (nums[cur] == 0) swap(nums[left++], nums[cur++]);
            else if (nums[cur] == 2) swap(nums[cur], nums[right--]);
            else cur++;
        }
    }
};
