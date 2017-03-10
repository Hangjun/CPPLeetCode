/*
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.
*/

// Time: O(m+n), Space: O(min(m, n)). Hash set.
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_set<int> ht(nums1.begin(), nums1.end());
        for (int n : nums2) {
            if (ht.count(n)) {
                res.push_back(n);
                ht.erase(n);
            }
        }
        return res;
    }
};
