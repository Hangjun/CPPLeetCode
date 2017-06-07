/*
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

// Bucket sort. Time: O(n), Space: O(n).
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty() || k == 0) return res;
        vector<vector<int>> bucket(nums.size()+1, vector<int>{});
        unordered_map<int, int> ht;
        for (int n : nums) ++ht[n];
        
        for (auto p : ht) bucket[p.second].push_back(p.first);
        
        for (int i = bucket.size()-1; i > 0; i--) {
            // if (bucket[i].empty()) continue;
            for (int j = 0; j < bucket[i].size() && res.size() < k; j++) {
                res.push_back(bucket[i][j]);
            }
        }
        
        return res;
    }
};
