/*
Given two strings S and T, determine if they are both one edit distance apart.
*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.size() > t.size())
            swap(s, t);
        if (t.size() - s.size() > 1) return false;
        bool have = false;
        for (int i = 0, j = 0; i < s.size(); i++, j++) {
            if (s[i] != t[j]) {
                if (have) {
                    return false;
                }
                have = true;
                if (s.size() < t.size()) {
                    i--;
                }
            }
        }
        return have || (s.size() < t.size());
    }
};
