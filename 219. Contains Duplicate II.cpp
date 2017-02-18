/*
Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at most k.
*/

/*
The bruteforce solution is, for every duplicating pair, compute their distance. A better solution is to use a set (just like part I of this problem) as a sliding windown of size k. This way as long as there is a duplicate found in this set, their distance is automatically less than k just by the construction of the set.
*/

// Time: O(n), Space: O(k)
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if (nums.empty() || k <= 0) return false;
        set<int> s; // sliding window set of size k
        
        for (int i = 0; i < nums.size(); i++) {
            if (s.size() > k) s.erase(nums[i-1-k]); // latest inserted number in s is nums[i-1]
            if (s.find(nums[i]) != s.end()) return true;
            s.insert(nums[i]);
        }
        
        return false;
    }
};
