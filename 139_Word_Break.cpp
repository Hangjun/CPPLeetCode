/*  Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or 
more dictionary words.

For example, given s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

/* The first idea is to use DFS/BFS. It turns out that we get TLE error when using DFS, but the BFS solution is accepted:

Time: O(n^2), Space: O(n)
*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty()) return false;
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> visited(s.size(), 0);
        queue<int> q;
        q.push(0);
        
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            if (visited[start]) continue;
            visited[start] = true;
            for (int end = start+1; end <= s.size(); end++) {
                if (!dict.count(s.substr(start, end-start)) || visited[end]) continue;
                if (end == s.size()) return true;
                q.push(end);
            }
        }
        
        return false;
    }
};

/*
Remark: We have to use a visited array in the above BFS. For example, s = "aaa", and the dictionary contains "a", "aa" and "aaa". From the first 'a', we will include both index 1 and 2 into the queue. Then at index 1 (the second 'a'), we will include index 2 into the queue again, hence the repeated search.
*/

/* 
Analysis: But this is reported Time Limit Exceeded. Therefore we need to optimize it. One way is to use dynamic programming:

Time: O(n^2), Space: O(n).
*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty()) return false;
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<bool> dp(n+1, false); // dp[i] = s[0:i-1] is breakable or not
        dp[0] = true; // empty strings are breakable
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (dp[j] && dict.count(s.substr(j, i-j+1))) dp[i+1] = true;
            }
        }
        
        return dp[n];
    }
};
