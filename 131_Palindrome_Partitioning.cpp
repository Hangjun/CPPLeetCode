/*
 Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        if (s.empty()) return res;
        vector<string> localSoln;
        // dp[i][j] = whether s[i,...,j] is palindromic
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        isPalindrome(s, dp);
        partitionDFS(s, 0, dp, localSoln, res);
        return res;
    }
    
    void partitionDFS(string s, int start, const vector<vector<bool>> &dp, vector<string> &localSoln, vector<vector<string>> &res) {
        // terminating condition
        if (start == s.size()) {
            res.push_back(localSoln);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            if (dp[start][i]) {
                localSoln.push_back(s.substr(start, i-start+1));
                // dfs
                partitionDFS(s, i+1, dp, localSoln, res);
                localSoln.pop_back();
            }
        }
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
