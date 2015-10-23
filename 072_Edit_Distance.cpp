Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

    Insert a character
    Delete a character
    Replace a character

/* Dynamic Programming: O(n^{2}) Time, O(n^{2}) Space */
class Solution {
public:    
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    int minDistance(string word1, string word2) {
        if (word1.empty())  return word2.size();
        if (word2.empty())  return word1.size();
        int m = word1.size();
        int n = word2.size();
        // dp[i][j] = dist(word1[0,...,i-1], word2[0,...,j-1])
        // return dp[m][n]
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        // initialize dp
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        // transfer function
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    // remove word1[i-1], or remove word2[j-1], or replace
                    // word1[i-1] with word2[j-1]
                    dp[i][j] = 1 + min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
                }
            }
        }
        return dp[m][n];
    }
};


