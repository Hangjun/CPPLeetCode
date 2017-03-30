/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/

/*
Analysis: This is obviously a DP problem. The state is also easy to define. The state transistion function in the case where s[i-1] == t[j-1] is slightly tricky. In that case, we simply have to options: either we take advantage of this and match t[0:j-2] in s[0:i-1], or we ignore this matching character.

Time: O(mn), Space: O(mn).
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        if (t.empty()) return 1;
        if (s.size() < t.size()) return 0;
        
        int m = s.size(), n = t.size();
        // dp[i][j] = number of subsequences of t[0:i-1] in s[0:j-1]
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i = 0; i <= m; i++) dp[i][0] = 1;
        for (int j = 1; j <= n; j++) dp[0][j] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = s[i-1] == t[j-1] ? (dp[i-1][j-1] + dp[i-1][j]) : dp[i-1][j];
            }
        }
        
        return dp[m][n];
    }
};

// Classic rolling array trick brings the space complexity down to O(min(m,n)).
class Solution {
public:
    int numDistinct(string s, string t) {
        if (t.empty()) return 1;
        if (s.size() < t.size()) return 0;
        
        int m = s.size(), n = t.size();
        // dp[i][j] = number of subsequences of t[0:i-1] in s[0:j-1]
        vector<vector<int>> dp(2, vector<int>(n+1, 0));
        for (int i = 0; i <= m; i++) dp[i%2][0] = 1;
        for (int j = 1; j <= n; j++) dp[0][j] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i%2][j] = s[i-1] == t[j-1] ? (dp[(i-1)%2][j-1] + dp[(i-1)%2][j]) : dp[(i-1)%2][j];
            }
        }
        
        return dp[m%2][n];
    }
};

/*
Remark: We claim that the space complexity can be further reduced to using a single row/column since dp[i][j] only depends on dp[i-1][j] and dp[i-1][j-1]. If it were to depend on dp[i-1][j] and dp[i][j-1], standard trick (rolling array +  recycle the same row/column) can be applied. However, the dependency on the previous diagnonal value is trickier. We will not go any further, but one can refer to Problem 221. Maximal Square (https://leetcode.com/problems/maximal-square/#/description) to see how we did it there with extra bookkeeping.
*/
