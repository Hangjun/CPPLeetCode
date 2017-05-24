/*
We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.
*/

/*
Analysis: This problem is very similar to a previous problem where the require the subsequence to be monotonically increasing with increments exactly 1. Here we simply keep the frequency of all elements x. The key observation is that, suppose x belongs to the longest subsequence, then the length = max(count[x] + count[x-1], count[x] + count[x+1]). Therefore we traverse the frequency table and compute this value for every x.

Time: O(n), Space: O(n). 2 Passes.
*/

class Solution {
public:
    int findLHS(vector<int>& nums) {
        int res = 0;
        unordered_map<int, int> count;
        for (int n : nums) count[n]++;
        
        for (auto p : count) {
            int cur = p.first;
            if (count.count(cur-1)) res = max(res, count[cur-1] + count[cur]);
            if (count.count(cur+1)) res = max(res, count[cur+1] + count[cur]);
        }
        
        return res;
    }
};

/*
Remark: We can actually do this in one pass: if one think about it more carefully, we are not going to miss count any number as we check, for every x, its lower value x-1 and upper value x+1.

Time: O(n), Space: O(n). 1 Pass.
*/

class Solution {
public:
    int findLHS(vector<int>& nums) {
        int res = 0;
        unordered_map<int, int> count;
        
        for (int n : nums) {
            count[n]++;
            if (count.count(n-1)) res = max(res, count[n-1] + count[n]);
            if (count.count(n+1)) res = max(res, count[n+1] + count[n]);
        }
        
        return res;
    }
};
