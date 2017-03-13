/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
*/

/* 
Analysis: Two pointer sliding window. Time: O(n), Space: O(1). One tricky part is when the right pointer hits the last element, we need to make sure to shrink the left pointer to calculate the window size. 
*/
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n <= 0 || s <= 0) return 0;
        int left = 0, right = -1, minLen = n+1;
        int sum = 0;
        while (right < n) {
            while (right < n && sum < s)
                sum += nums[++right];
            if (sum >= s) {
                minLen = min(minLen, right-left+1);
                sum -= nums[left++];
            }
        }
        
        return minLen == n+1? 0 : minLen;
    }
};

// A more careful implementation of the above algorithm is to terminate on left == n
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty() || s <= 0) return 0;
        int left = 0, right = 0;
        int n = nums.size();
        int minLen = n+1;
        int sum = 0;
        while (left < n) { // since we are computing min size window, need to shrink left to not shrinkable
            while (right < n && sum < s) sum += nums[right++];
            if (sum >= s) {
                minLen = min(minLen, right-left);
                sum -= nums[left++];
            } else {
                break; // not able to reach the sum s
            }
        }
        return minLen == n+1 ? 0 : minLen;
    }
};

// Binary search the window size. Time: O(nlogn), Space: O(1).
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty() || s <= 0) return 0;
        int l = 1, u = nums.size();
        int res = nums.size()+1;
        while (l <= u) {
            int mid = l + (u-l)/2;
            if (windowExists(mid, nums, s)) {
                res = mid;
                u = mid-1;
            } else {
                l = mid+1;
            }
        }
        return res == nums.size()+1 ? 0 : res;
    }
    
    bool windowExists(int k, vector<int> &nums, int s) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i >= k) sum -= nums[i-k];
            sum += nums[i];
            if (sum >= s) return true;
        }
        return false;
    }
};

/* 
Another algorithm is to first construct the partial sum array. Then for every index of the partial sum array, binary search for its upper bound.

Time: O(nlogn), Space: O(n).
*/
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty() || s <= 0) return 0;
        int n = nums.size();
        int res = n+1;
        vector<int> ps(n+1, 0); // ps[i] = nums[0] + nums[1] + ... + nums[i-1]
        for (int i = 0; i < n; i++) ps[i+1] = ps[i] + nums[i];
        
        for (int i = 0; i < n; i++) {
            res = min(res, binarySearch(nums, ps, i, s)); // find minimum right upper bound for left lower bound = ps[i+1]
        }
        return res == n+1 ? 0 : res;
    }
    
    int binarySearch(vector<int> &nums, vector<int> &ps, int start, int s) {
        int left = start, right = nums.size();
        while (left <= right) {
            int mid = left + (right-left)/2;
            if (ps[mid]-ps[start] < s) {
                left = mid+1;
            } else {
                if (ps[mid-1]-ps[start] < s) return mid-start;
                else right = mid-1;
            }
        }
        return nums.size()+1;
    }
};


