/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

/* 
Analysis: We can solve this problem by turning it into a 1Sum + 2Sum problem: we first sort the array, then for every element in the array, we find its 3Sum complements using colliding two pointers.

The key is to be careful about avoiding duplicates solutions. Duplicates can happen in the outer 1Sum loop as well as in the inner 2Sum loop.

Time: O(n^2), Space: O(1).
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-2; i++) {
            // remove dupicate solutions in the outer 1Sum loop
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int left = i+1, right = nums.size()-1;
            while (left < right) {
                if (nums[left] + nums[right] + nums[i] == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                    // remove dupicates in the inner 2Sum loop
                    while (left < right && nums[left] == nums[left-1]) left++;
                    while (left < right && nums[right] == nums[right+1]) right--;
                }  else if (nums[left] + nums[right] + nums[i] < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
};
