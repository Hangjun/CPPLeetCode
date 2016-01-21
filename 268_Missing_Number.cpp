/*
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity? 
*/

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int res = (1 + n) * n / 2;
        for (int j = 0; j < n; j++) {
            res -= nums[j];
        }
        return res;
    }
};

