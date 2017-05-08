/*
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
*/

// Time: O(n), Space: O(n).
class Solution {
public:
    int firstUniqChar(string s) {
        if (s.size() < 2) return s.empty() ? -1 : 0;
        unordered_map<char, vector<int>> ht; // character -> indices at which it occurs
        for (int i = 0; i < s.size(); i++) {
            ht[s[i]].push_back(i);
        }
        int res = INT_MAX;
        for (auto p : ht) {
            if (p.second.size() > 1) continue;
            res = min(res, p.second[0]);
        }
        return res == INT_MAX ? -1 : res;
    }
};
