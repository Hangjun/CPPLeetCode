/*
Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

Example

Given the string = "abcdzdcab", return "cdzdc".
Challenge

O(n2) time is acceptable. Can you do it in O(n) time.
*/

/* 
DP Solution. Time: O(n^2), Space: O(n^2).
*/
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        int n = s.size();
        int maxLen = 0;
        int start = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        // This is the joseki for computing whether any substring s[i...j] is palindromic. Memorize it!
        for (int i = n-1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if ((j - i < 2 || dp[i+1][j-1]) && s[i] == s[j]) {
                    dp[i][j] = true; // this also includes the initial state of dp[i][i] being true, for all i
                    if (j - i + 1 > maxLen) {
                        maxLen = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
};
