/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space. 
*/

/* Submission #1: Failed: 
Submission Result: Time Limit Exceeded
Last executed input: [1,1] 
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        // the first missing positive must be within (0, n]
        int i = 0; 
        while (i < n) {
            if (nums[i] != i+1 && nums[i] > 0 && nums[i] <= n) {
                // nums[i] is miss-placed: any number x should be placed at nums[x-1]
                swap(nums[i], nums[nums[i]-1]);
            } else {
                i++;
            }
        }
        for (i = 0; i < nums.size(); i++) {
            if (nums[i] != i+1) {
                return i+1;
            }
        }
        return n+1;
    }
};

/* 
Re-run the above input with our implementation, we see that line 25 gets executed infinitely when i = 1. 
*/

// Submission #2: Accepted

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        // the first missing positive must be within (0, n]
        int i = 0; 
        while (i < n) {
            if (nums[i] != i+1 && nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i]-1]);
            } else {
                i++;
            }
        }
        for (i = 0; i < nums.size(); i++) {
            if (nums[i] != i+1) {
                return i+1;
            }
        }
        return n+1;
    }
};
