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

// Submission #1: Failed - Wrong Answer
class Solution {
public:
    bool isMatch(string s, string p) {
        // corner cases
        if (s.empty()) return p.empty();
        if (p.empty()) return s.empty();
        
        // pStar marks the '*' location of p
        // p[pStar] matches part of s until sStar-1 
        int sStar = -1, pStar = -1;
        int i = 0, j = 0;
        while (i < s.size()) {
            if (s[i] == p[j] || p[j] == '?') {
                i++;
                j++;
            } else if (p[j] == '*') {
                pStar = j;
                sStar = i;
                j++;
            } else if (pStar != -1) {
                // backtrack
                j = pStar + 1;
                i = ++sStar;
            } else {
                return false;
            }
        }
        // now s is fully traversed
        while (j < p.size() && p[j] == '*') j++;
        return j == p.size();
    }
};

/* 
The above failed due to line #27: if s.empty() the matching still returns true as long as p consists of only '*'s. In fact, this condition
is covered by the while-loop on line #34. After deleting line #27, the code passes the OJ:
*/

// Submission #2: Accepted
class Solution {
public:
    bool isMatch(string s, string p) {
        // corner cases
        if (p.empty()) return s.empty();
        
        // pStar marks the '*' location of p
        // p[pStar] matches part of s until sStar-1 
        int sStar = -1, pStar = -1;
        int i = 0, j = 0;
        while (i < s.size()) {
            if (s[i] == p[j] || p[j] == '?') {
                i++;
                j++;
            } else if (p[j] == '*') {
                pStar = j;
                sStar = i;
                j++;
            } else if (pStar != -1) {
                // backtrack
                j = pStar + 1;
                i = ++sStar;
            } else {
                return false;
            }
        }
        // now s is fully traversed
        while (j < p.size() && p[j] == '*') j++;
        return j == p.size();
    }
};
