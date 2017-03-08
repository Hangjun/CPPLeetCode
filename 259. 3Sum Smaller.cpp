/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]
Follow up:
Could you solve it in O(n2) runtime?
*/

/*
Time: O(n^2), Space: O(1).
*/
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int count = 0;
        if (nums.size() < 3) return count;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-2; i++) {
            // no need to de-dup: including all solutions
            int left = i+1, right = nums.size()-1;
            while (left < right) {
                int curSum = nums[i]+nums[left]+nums[right];
                if (curSum >= target) {
                    right--;
                } else {
                    count += right-left; // add up (i, left, right), (i, left, right-1), ..., (i, left, left+1)
                    left++;
                }
                                                                                                          
            }
        }
        return count;
    }
};
