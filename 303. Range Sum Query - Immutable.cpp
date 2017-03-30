/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
*/

class NumArray {
public:
    NumArray(vector<int> nums) {
        int v = 0;
        partialSum.push_back(v);
        for (int n : nums) {
            partialSum.push_back(n + v);
            v += n;
        }
    }
    
    int sumRange(int i, int j) {
        return partialSum[j+1] - partialSum[i];
    }

private:
    vector<int> partialSum; // partialSum[i] = nums[0] + ... + nums[i-1] 
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
