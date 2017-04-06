/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 
*/

// Solution #1: The is obviously a DP problem. In particular, this is a DP cut problem. 
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        if (n <= 1)  return 0;
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        isPalindrome(s, isPal);
        // dp[i] = min cut for the prefix s[0,...,i-1]
        vector<int> dp(n+1, INT_MAX);
        dp[0] = -1;
        for (int i = 1; i <= n; i++) {
            for (int j = i-1; j>=0; j--) {
                if (isPal[j][i-1]) {
                    // min cuts in s[0,...,j-1] plus the one cut s[j,...,i-1]
                    dp[i] = min(dp[i], dp[j]+1);
                }
            }
        }
        return dp[n];
    }
    
    void isPalindrome(string s, vector<vector<bool>> &dp) {
        int len = s.size();
        for (int i = len-1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if ((j-i <= 2 || dp[i+1][j-1]) && s[i] == s[j])
                    dp[i][j] = true;
            }
        }
    }
};

/* Solution #2:
We can optimize the space utilization to O(1). Here is the key idea: suppose we let cut[i] to be the minimum number of cuts for the first 
i characters, i.e. the substring s[0,...,i-1]. Suppose that we are now at s[i], which is b. Its neighboring charac- ters are s[0], 
s[0], ..., a, b, a, s[i+2],.... Since s[i-1, i, i+2] is palindromic, cut[i+2] (min cuts for s[0,...,i+1]) is no greater than cut[i-1] + 1. 
This makes use of the symmetric property of palindromic strings. The case with even number of characters can be handled in a similar 
fashion.
*/

class Solution {
public:
    int minCut(string s) {
        /* O(n^{2}) Time, O(1) Space */
        int n = s.size();
        if (n <= 1)  return 0;
        // cut[i] = min # cut for s[0,...,i-1]
        vector<int> cut(n+1, 0);
        // initialize cut
        for (int i = 0; i <= n; i++)
            cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            // odd palindromic substring centered at i
            for (int j = 0; j <= i && i+j < n && s[i+j] == s[i-j]; j++)
                cut[i+j+1] = min(cut[i+j+1], 1+cut[i-j]);
            // even palindromic substring centered at i&&i+1
            for (int j = 1; j <= i+1 && i+j < n && s[i-j+1] == s[i+j]; j++)
                // s[i-(j-1),...,i-1] == s[j+1,...,i+j]
                cut[i+j+1] = min(cut[i+j+1], 1+cut[i-j+1]);
        }
        return cut[n];
    }
};

// Solution: #3: Another implementation of the above algorithm.
class Solution {
public:
    int minCut(string s) {
        /* O(n^{2}) Time, O(n) Space */
        int n = s.size();
        if (n <= 1)  return 0;
        // cut[i] = min # cut for s[0,...,i]
        vector<int> cut(n, INT_MAX);
        // initialize cut
//        for (int i = 0; i < n; i++)
            cut[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i && i+j < n && s[i+j] == s[i-j]; j++) {
                if (j == i) {
                    cut[i+j] = min(cut[i+j], 0);
                } else {
                    cut[i+j] = min(cut[i+j], 1+cut[i-j-1]);
                }
            }
            for (int j = 1; j <= i + 1 && i+j < n && s[i+j] == s[i-j+1]; j++) {
                if (j == i + 1) {
                    cut[i+j] = min(cut[i+j], 0);
                } else {
                    cut[i+j] = min(cut[i+j], 1+cut[i-j]);
                }
            }
        }
        return cut[n-1];
    }
};
