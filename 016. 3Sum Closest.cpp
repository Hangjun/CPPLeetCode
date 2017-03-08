/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

/*
Analysis: Similar solution to 3Sum, but this time we need to keep track of the different between the every tripets and the target value.

Time: O(n^2), Space: O(1).
*/
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int minDiff = INT_MAX;
        if (nums.size() < 3) return minDiff;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int left = i+1, right = nums.size()-1;
            while (left < right) {
                int curDiff = nums[i]+nums[left]+nums[right]-target;
                if (abs(curDiff) < abs(minDiff)) minDiff = curDiff;
                if (curDiff == 0) break;
                else if (curDiff < 0) left++;
                else right--;
            }
        }
        return minDiff + target;
    }
};
