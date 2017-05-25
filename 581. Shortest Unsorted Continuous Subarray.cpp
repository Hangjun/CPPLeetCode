/*
Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.
*/

// Time: O(n), Space: O(1). 1 Pass.
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size(), curMax = nums[0], curMin = nums[n-1];
        int begin = -1, end = -2;
        
        for (int i = 1; i < n; i++) {
            curMax = max(curMax, nums[i]);
            curMin = min(curMin, nums[n-1-i]);
            
            if (nums[i] < curMax) end = i;
            if (nums[n-1-i] > curMin) begin = n-1-i;
        }
        
        return end - begin + 1;
    }
};

// An easier to understand solution takes 2 passes:
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size(), left = nums[n-1], right = nums[0];
        for (int i = 0; i < n-1; i++) {
            if (nums[i] > nums[i+1]) {
                left = i;
                break;
            }
        }
        
        for (int j = n-1; j > 0; j--) {
            if (nums[j] < nums[j-1]) {
                right = j;
                break;
            }
        }
        
        if (left >= right) return 0;
        int curMax = INT_MIN, curMin = INT_MAX;
        for (int i = left; i <= right; i++) {
            curMax = max(curMax, nums[i]);
            curMin = min(curMin, nums[i]);
        }
        
        while (left >= 0 && nums[left] > curMin) left--;
        while (right < n && nums[right] < curMax) right++;
        
        return right-left-1;
    }
};
