/*
 Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        int localMax = nums[0], localMin = nums[0];
        int globalMax = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int tmpMax = localMax;
            localMax = max(nums[i], max(localMax * nums[i], localMin * nums[i]));
            localMin = min(nums[i], min(tmpMax * nums[i], localMin * nums[i]));
            globalMax = max(globalMax, localMax);
        }
        return globalMax;
    }
};
