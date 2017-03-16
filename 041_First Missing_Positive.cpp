/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space. 
*/

/* Analysis:
First to quote a "Da Shen": given an unsorted array with linear time requirements, a hash table is usually used. Since we are also required 
to use only constant space, we use the array it self as a hash table: nums: i ---> i+1. Thus if we can get each entry x placed into its 
"correct" position nums[x-1], then we can locate the first missing positive by a second linear scan. 

A desired first missing positive, say x, has to satisfy 0 < x <= n, where n = nums.size(). Moreover, if nums[i] = i+1, then x = i+1 is already 
in the "correct position". If a entry satisfies 0 < nums[i] <= n, and nums[i] != i+1, then we need to move it to its correct position which 
is nums[nums[i] - 1]. However, after the swap, there are potentially two problems:
1. The newly swaape in element nums[nums[i] - 1] might still be out of place. Thus we cannot incremnt the cursor i after the swap.
2. If nums[i] == nums[nums[i] - 1], then if we do the swap without checking this, we will result in an infinite loop: we will keep swapping 
forever. 

Therefore we need to check all four conditions before swapping: see line 32.
*/

// Time: O(n), Space: O(1). 2 Passes.
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[i] != i+1 && nums[nums[i]-1] != nums[i]) 
                swap(nums[i], nums[nums[i]-1]);
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i+1) return i+1;
        }
        return n+1;
    }
};
