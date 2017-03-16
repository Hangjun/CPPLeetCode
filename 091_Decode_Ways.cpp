/*
 A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2. 
*/

// Dynamic Programming with rolling array space optimization. Time: O(n), Space: O(1).
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        if (s.size() == 1) return validOne(s[0]);
        
        int n = s.size(); // now n >= 2
        vector<int> dp(3, 0); // dp[i] = number of decode ways for s[0:i]
        // initialize dp[0]
        if (!validOne(s[0])) return 0;
        dp[0] = 1;
        
        if (validOne(s[1])) {
            dp[1] = dp[0];
            if (validTwo(s[0], s[1])) dp[1]++;
        } else {
            if (validTwo(s[0], s[1])) dp[1] = 1;
            else return 0;
        }
        
        for (int i = 2; i < n; i++) {
            if (validOne(s[i]) && validTwo(s[i-1], s[i])) dp[i%3] = dp[(i-1)%3] + dp[(i-2)%3];
            if (validOne(s[i]) && !validTwo(s[i-1], s[i])) dp[i%3] = dp[(i-1)%3];
            if (!validOne(s[i]) && validTwo(s[i-1], s[i])) dp[i%3] = dp[(i-2)%3];
            if (!validOne(s[i]) && !validTwo(s[i-1], s[i])) return 0;
        }
        return dp[(n-1)%3];
    }
    
    bool validOne(char c) {
        return c >= '1' && c <= '9';
    }
    
    bool validTwo(char a, char b) {
        return a == '1' || (a == '2' && b <= '6');
    }
};
