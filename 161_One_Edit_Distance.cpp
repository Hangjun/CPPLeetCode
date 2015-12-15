/*
Given two strings S and T, determine if they are both one edit distance apart.
*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        // make the first string the one with smaller size
        if (s.size() > t.size()) {
            return isOneEditDistance(t, s);
        }
        // check if the size differ by more than one
        if (t.size() - s.size() > 1) return false;
        bool haveDiffered = false;
        for (int i = 0, j = 0; i < s.size(); i++, j++) {
            if (s[i] != t[j]) {
                if (haveDiffered) return false;
                haveDiffered = true;
                // if s.size() < t.size() (as opposed to s.size() == t.size(),
                // we need to make i stay by decrementing it by one
                if (s.size() < t.size()) {
                    i--;
                }
            }
        }
        // caution: at this point if s.size() == t.size() && !haveDiffered, then 
        // s and t are identical: need to report false;
        return haveDiffered || s.size() < t.size();
    }
};
