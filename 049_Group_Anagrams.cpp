/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    For the return value, each inner list's elements must follow the lexicographic order.
    All inputs will be in lower-case.
*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if (strs.empty())  return res;
        map<vector<int>, vector<string>> ht;
        for (int i = 0; i < strs.size(); i++) {
            vector<int> count(26, 0);
            string s = strs[i];
            for (int j = 0; j < s.size(); j++)
                ++count[s[j]-'a'];
            ht[count].push_back(s);
        }
        for (auto n:ht) {
            sort(n.second.begin(), n.second.end());
            res.push_back(n.second);
        }
        return res;
    }
};
