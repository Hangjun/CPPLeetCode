/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

/* Submission #1: Failed: 
Submission Result: Runtime Error
Last executed input: "aasdfasdfasdfasdfas"
"aasdf.*asdf.*asdf.*asdf.*s" 
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size();
        int n = p.size();
        // dp[i][j] = isMatch(s[0,...,i-1], p[0,...,j-1])
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) { // do not care empty pattern
                if (p[j-1] != '*' && p[j-1] != '*') {
                    dp[i][j] = (p[j-1] == s[i-1]) && dp[i-1][j-1];
                } else if (p[j-1] != '*') {
                    dp[i][j] = dp[i-1][j-1];
                } else { // p[j-1] == '*'
                    assert(j > 1); // cannot be the first character
                    // dp[i][j] = match 0 or 1 or more of the previous character
                    dp[i][j] = (dp[i][j-2] || dp[i][j-1] || ((p[j-2] == s[i-1] || p[j-2] == '.') && dp[i-1][j]));
                }
            }
        }
        return dp[m][n];
    }
};

/* Analysis:
As a fundamental principle: whenever we write i-1 or j-1, check i > 0, j > 0! Bugs on lines 40, 42 and 46.
*/

/* Submission #2: Failed:
Submission Result: Wrong Answer
Input: "aaa"
"a.a"
Output: false
Expected: true 
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size();
        int n = p.size();
        // dp[i][j] = isMatch(s[0,...,i-1], p[0,...,j-1])
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) { // do not care empty pattern
                if (p[j-1] != '*' && p[j-1] != '*') {
                    dp[i][j] = i > 0 && p[j-1] == s[i-1] && dp[i-1][j-1];
                } else if (p[j-1] == '.') {
                    dp[i][j] = i > 0 && dp[i-1][j-1];
                } else { // p[j-1] == '*'
                    assert(j > 1); // cannot be the first character
                    // dp[i][j] = match 0 or 1 or more of the previous character
                    dp[i][j] = (dp[i][j-2] || dp[i][j-1] || (i > 0 && (p[j-2] == s[i-1] || p[j-2] == '.') && dp[i-1][j]));
                }
            }
        }
        return dp[m][n];
    }
};

/* Analysis:
Typo on line 76.
*/

// Submission #3: Accepted.
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size();
        int n = p.size();
        // dp[i][j] = isMatch(s[0,...,i-1], p[0,...,j-1])
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) { // do not care empty pattern
                if (p[j-1] != '.' && p[j-1] != '*') {
                    dp[i][j] = i > 0 && p[j-1] == s[i-1] && dp[i-1][j-1];
                } else if (p[j-1] == '.') {
                    dp[i][j] = i > 0 && dp[i-1][j-1];
                } else { // p[j-1] == '*'
                    assert(j > 1); // cannot be the first character
                    // dp[i][j] = match 0 or 1 or more of the previous character
                    dp[i][j] = (dp[i][j-2] || dp[i][j-1] || (i > 0 && (p[j-2] == s[i-1] || p[j-2] == '.') && dp[i-1][j]));
                }
            }
        }
        return dp[m][n];
    }
};
