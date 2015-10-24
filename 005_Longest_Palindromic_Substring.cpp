Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

Example

Given the string = "abcdzdcab", return "cdzdc".
Challenge

O(n2) time is acceptable. Can you do it in O(n) time.

/* Dynamic Programming Solution: O(n^2) Time, O(n^2) Space: Time Limit Exceeded by LeetCode OJ */
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        if (len <= 1)  return s;
        // dp[i][j]: whether s[i,...,j] is palindrome
        vector<vector<bool>> dp(len, vector<bool>(len, false));
        int maxLen = 1;
        int start = 0;
        for (int i = len-1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if ((j-i<=2 || dp[i+1][j-1] == true) && s[i] == s[j]) {
                    dp[i][j] = true;
                    if (j-i+1 > maxLen) {
                        maxLen = j-i+1;
                        start = i;
                    }
                }
            }
        }
        // now the maxLen palindrome substring starts at i
        return s.substr(start, maxLen);
    }
};

Note: O(n) Time solution to be updated. 
