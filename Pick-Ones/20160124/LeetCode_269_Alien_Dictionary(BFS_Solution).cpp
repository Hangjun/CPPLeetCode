/*
 There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

The correct order is: "wertf".

Note:

    You may assume all letters are in lowercase.
    If the order is invalid, return an empty string.
    There may be multiple valid order of letters, return any one of them is fine.
*/

// We revisit this problem with a BFS solution using the notion of in-degrees.

// Submission #1: Accepted.
class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.empty()) return "";
        if (words.size() == 1) return words[0];
        string order = "";
        unordered_map<char, int> inDegree;
        unordered_map<char, vector<char>> partialOrder;
        int totalDegree = 0;
        for (int i = 0; i < words.size() -1; i++) {
            string s = words[i];
            string t = words[i+1];
            int len = max(s.size(), t.size());
            bool found = false;
            for (int j = 0; j < len; j++) {
                // "warm up" the inDegree table
                if (j < s.size() && inDegree.find(s[j]) == inDegree.end()) {inDegree[s[j]] = 0;}
                if (j < t.size() && inDegree.find(t[j]) == inDegree.end()) {inDegree[t[j]] = 0;}
                // if s[j] != t[j], and we havn't recorded the first difference yet, record it
                if (j < s.size() && j < t.size() && s[j] != t[j] && !found) {
                    // s[j] proceeds t[j]
                    partialOrder[s[j]].push_back(t[j]);
                    inDegree[t[j]]++;
                    found = true;
                }
            }
        }
        queue<char> q;
        for (auto it = inDegree.begin(); it != inDegree.end(); it++) {
            totalDegree += it->second;
            if (it->second == 0) {
                q.push(it->first);
            }
        }
        while (!q.empty()) {
            char curChar = q.front();
            order.push_back(curChar);
            q.pop();
            // check if curChar proceeds any other characters
            if (partialOrder[curChar].empty()) continue;
            for (auto it = partialOrder[curChar].begin(); it != partialOrder[curChar].end(); it++) {
                --totalDegree;
                if(--inDegree[*it] == 0) {
                    q.push(*it);
                }
            }
        }
        // check if any character's indegree is still positive
        return totalDegree == 0 ? order : "";
    }
};
