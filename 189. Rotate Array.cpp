/*
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

[show hint]

Hint:
Could you do it in-place with O(1) extra space?
Related problem: Reverse Words in a String II
*/

// Time: O(n), Space: O(1). In place solution.
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.empty() || !k) return;
        int n = nums.size();
        k = k % n;
        reverseArray(nums, 0, n-k-1);
        reverseArray(nums, n-k, n-1);
        reverseArray(nums, 0, n-1);
    }
    
    void reverseArray(vector<int> &nums, int start, int end) {
        if (start > end) return;
        while (start < end) swap(nums[start++], nums[end--]);
    }
};
