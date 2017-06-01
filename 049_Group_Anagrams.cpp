/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note: For the return value, each inner list's elements must follow the lexicographic order. All inputs will be in lower-case.
*/

/*
Analysis: We build a hash tables for anagrams with keys their character histograms.

Time: O(mn), where m = |strs|, and n = average length of strings. Space: O(mn).
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if (strs.empty()) return res;
        
        map<vector<int>, vector<string>> ht; // histogram -> strings with that histogram
        for (string s : strs) {
            vector<int> hist(256, 0);
            for (char c : s) ++hist[c-'a'];
            ht[hist].push_back(s);
        }
        
        for (auto p : ht) {
            sort(p.second.begin(), p.second.end());
            res.push_back(p.second);
        }
        
        return res;
    }
};
