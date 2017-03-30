/*
Total Accepted: 66056
Total Submissions: 273403
Difficulty: Hard
Contributor: LeetCode
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/

/*
Analysis: This is obviously a DP problem. Tricky part here is how to use DP to represent the turn taking here. We can let the DP table represents if s3 is interleaving at (i+j)th position when s1 is at ith position, and s2 is at jth position. 0th position means empty string.

So if both s1 and s2 is currently empty, s3 is empty too, and it is considered interleaving. If only s1 is empty, then if previous s2 position is interleaving and current s2 position char is equal to s3 current position char, it is considered interleaving. similar idea applies to when s2 is empty. when both s1 and s2 is not empty, then if we arrive i, j from i-1, j, then if i-1,j is already interleaving and i and current s3 position equal, it s interleaving. If we arrive i,j from i, j-1, then if i, j-1 is already interleaving and j and current s3 position equal. it is interleaving.

Time: O(mn), Space: O(mn).
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (s3.size() != m + n) return false;
        // dp[i][j] = whether s3 is interleaving at (i+j-1)th element if s1 is at the ith, s2 is at the jth element, resp.
        vector<vector<bool>> dp (m+1, vector<bool>(n+1, false)); 
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
               if (i == 0 && j == 0) dp[i][j] = true;
               else if (i == 0) dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i+j-1];
               else if (j == 0) dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i+j-1];
               else dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        return dp[m][n];
    }
};

// We can use the method of rolling arrays to reduce the space complexity to O(min(m,n)). 2 Rows.
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (s3.size() != m + n) return false;
        // dp[i][j] = whether s3 is interleaving at (i+j-1)th element if s1 is at the ith, s2 is at the jth element, resp.
        vector<vector<bool>> dp (2, vector<bool>(n+1, false)); 
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
               if (i == 0 && j == 0) dp[i%2][j] = true;
               else if (i == 0) dp[i%2][j] = dp[i%2][j-1] && s2[j-1] == s3[i+j-1];
               else if (j == 0) dp[i%2][j] = dp[(i-1)%2][j] && s1[i-1] == s3[i+j-1];
               else dp[i%2][j] = (dp[(i-1)%2][j] && s1[i-1] == s3[i+j-1]) || (dp[i%2][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        return dp[m%2][n];
    }
};

// We can further reduce the space complexity to only one row. 
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (s3.size() != m + n) return false;
        // dp[i][j] = whether s3 is interleaving at (i+j-1)th element if s1 is at the ith, s2 is at the jth element, resp.
        vector<bool> dp(n+1, false);
        dp[0] = true;
        for (int j = 1; j <= n; j++) dp[j] = dp[j-1] && s2[j-1] == s3[j-1];
        
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
               if (j == 0) dp[j] = dp[j] && s1[i-1] == s3[i+j-1];
               else dp[j] = (dp[j] && s1[i-1] == s3[i+j-1]) || (dp[j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        return dp[n];
    }
};
