/*
Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.

Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
Note:
The pairs (i, j) and (j, i) count as the same pair.
The length of the array won't exceed 10,000.
All the integers in the given input belong to the range: [-1e7, 1e7].
*/

/*
Analysis: The tricky part of this problem is de-duplication. A valid solution must be numbers of two distinct indices. Mover, we cannot have more than one solution that is the exact same pair.

For example, [1,1,1,1,1] and k = 0 returns only 1 solution [1,1].

Time: O(n), Space: O(n). Hash table.
*/
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (nums.empty() || k < 0) return 0;
        int res = 0;
        unordered_map<int, int> ht; // number -> count
        for (int n : nums) ++ht[n];
        for (auto p : ht) res += k == 0 ? p.second >= 2 : ht.find(p.first+k) != ht.end();
        return res;
    }
};
