/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int sStar = -1, pStar = -1;
        int i = 0, j = 0;
        while (i < s.size()) {
            if (s[i] == p[j] || p[j] == '?') {
                i++;
                j++;
            } else if (p[j] == '*') {
                sStar = i;
                pStar = j++;
            } else if (pStar != -1) {
                // backtrack
                i = ++sStar;
                j = pStar + 1;
            } else {
                return false;
            }
        }
        // s is fully traversed: check if p remains only '*'s
        while (j < p.size() && p[j] == '*') j++;
        return j == p.size();
    }
};
