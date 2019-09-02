/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S. 
*/

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";
        vector<int> needToFind(256, 0);
        vector<int> hasFound(256, 0);
        for (int i = 0; i < t.size(); i++) {
            needToFind[t[i]]++;
        }
        int minLen = INT_MAX;
        int minStart = -1;
        int count = 0; // counts the number of characters found
        int i = 0;
        for (int j = 0; j < s.size(); j++) {
            if (needToFind[s[j]] == 0) continue;
            if (hasFound[s[j]]++ < needToFind[s[j]]) { count++; }
            if (count == t.size()) { // found all of t's characters
                // compute window size: shrink i to the right as far as possible before
                while (needToFind[s[i]] == 0 || hasFound[s[i]] > needToFind[s[i]]) {
                    if (needToFind.count(s[i]) && hasFound[s[i]] > needToFind[s[i]]) {
                        hasFound[s[i]]--;
                    }
                    i++;
                }
                if (minLen > j - i + 1) {
                    minLen = j - i + 1;
                    minStart = i;
                }
            }
        }
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};
