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

class Solution {
public:
    int numDecodings(string s) {
        // corner cases
        if (s.empty()) return 0;
        int n = s.size();
        if (n == 1) {
            return validOneDigit(s[0]) ? 1 : 0;
        }
        // dp[i] = number of ways to decode s[0,..,i]
        vector<int> dp(n);
        // now s has at least two chars, initialize dp[0] and dp[1]
        if (validOneDigit(s[0])) {
            dp[0] = 1;
        } else {
            return 0;
        }
        if (validOneDigit(s[1])) {
            dp[1] = dp[0];
            if (validTwoDigits(s.substr(0, 2))) {
                dp[1]++;
            }
        } else {
            if (validTwoDigits(s.substr(0, 2))) {
                dp[1] = 1;
            } else {
                return 0;
            }
        }
        // state transfer function:
        // dp[i] = dp[i-1] + (s[i-1,i] <= 26) ? dp[i-2] : 0
        for (int i = 2; i < n; i++) {
            if (validOneDigit(s[i])) {
                dp[i] = dp[i-1];
                if (validTwoDigits(s.substr(i-1, 2))) {
                    dp[i] += dp[i-2];
                }
            } else {
                if (validTwoDigits(s.substr(i-1, 2))) {
                    dp[i] = dp[i-2];
                } else {
                    return 0;
                }
            }
        }
        return dp[n-1];
    }
    
    bool validOneDigit(char c) {
        return c >= '1' && c <= '9';
    }
    
    bool validTwoDigits(string s) {
        return s[0] >= '1' && s[0] <= '2' && stoi(s) <= 26;
    }
};
