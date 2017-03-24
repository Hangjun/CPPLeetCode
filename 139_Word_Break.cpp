/*  Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or 
more dictionary words.

For example, given s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

// The first idea is to use DFS:

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if (s.empty() || wordDict.empty()) return false;
        return wordBreakDFS(s, 0, wordDict);
    }
    // invariant: s.substr(0,start-1) is already found, testing s.substr(start)
    bool wordBreakDFS(string s, int start, unordered_set<string> &wordDict) {
        // terminate condition
        if (start == s.size())  return true;
        
        for (int i = start; i < s.size(); i++) {
            string curWord = s.substr(start, i-start+1);
            if (wordDict.count(curWord)) {
                // recurse on curWord
                if (wordBreakDFS(s, i+1, wordDict)) {
                    return true;
                }
            }
        }
        return false;
    }
};

/* 
Analysis: But this is reported Time Limit Exceeded. Therefore we need to optimize it. One way is to use dynamic programming:
*/

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if (wordDict.empty()) return false;
        if (s.empty()) return true; // empty string is trivially breakable
        int n = s.size();
        // dp[i] = whether s[0,..,i-1] is breakable
        vector<int> dp(n+1, false);
        dp[0] = true;
        
        // state transfer: dp[i] = true iff s[0,...,j-1] is breakable
        // wordDict and s[j,...,i] exists in wordDict
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (dp[j] && wordDict.count(s.substr(j, i-j+1)))
                    dp[i+1] = true;
            }
        }
        return dp[n];
    }
};
