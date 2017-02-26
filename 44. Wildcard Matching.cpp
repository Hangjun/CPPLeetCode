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

// Iterative/Greedy Algorithm:
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int i = 0, j = 0;
        int sStar = -1, pStar = -1;
        while (i < s.size()) {
            if (s[i] == p[j] || p[j] == '?') {
                i++;
                j++;
            } else if (p[j] == '*') {
                sStar = i;
                pStar = j;
                j++;
            } else if (pStar != -1) {
                j = pStar+1;
                i = ++sStar;
            } else {
                return false;
            }
        }
        while (p[j] == '*') j++;
        return j == p.size();
    }
};

/*
Below is the standard DP solution (Time O(mn), Space O(mn)). We needed the trick inline to get LOJ pass, otherwise it will trigger the TLE exceptiond due to the quardratic running time.

One key observation in the state transfer function when p[j-1] == '*' is that, techniquely we have:
dp[i][j] = dp[i][j-1] || dp[i-1][j-1] || dp[i-2][j-1] || ... || dp[0][j-1], that corresponds to p[j-1] matching 0, 1, 2, ... characters in s. To simpify this equation, we note that:
dp[i-1][j] = dp[i-1][j-1] || dp[i-2][j-1] || ... || dp[0][j-1]. Therefore: dp[i][j] = dp[i][j-1] || dp[i-1][j].
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size(), n = p.size();
        // if (n > 30000) return false; // trick to the avoid the TLE
        vector<vector<int>> dp(m+1, vector<int>(n+1, false)); // dp[i][j] = isMatch(s[0,...,i-1], p[0,...,j-1])
        // initialization
        dp[0][0] = true;
        for (int j = 1; j <= n; j++) dp[0][j] = (p[j-1] == '*' && dp[0][j-1]);
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == '*') {
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                } else if (p[j-1] == s[i-1] || p[j-1] == '?') {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
        return dp[m][n];
    }
};
