/*
Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".
Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".
*/

/*
We can simply modify the "joseki" DP in Problem 5. Longest Palindromic Substring.

Time: O(n^2), Space: O(n^2).
*/

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.size() <= 1) return s.size();
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0)); // dp[i][j] = length of the lps in s[i...j]
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        
        for (int i = n-1; i >= 0; i--) {
            for (int j = i+1; j < n; j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = (j == i+1 ? 0 : dp[i+1][j-1]) + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[0][n-1];
    }
};
