/*
Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

Example 1:
Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
*/

/*
Analysis: We build a KMP table to solve this problem.

Time: O(n), Space: O(n).
*/
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        vector<int> dp(n+1, 0); // dp[i+1] = longest prefix that's also a suffix up to i
        int i = 1, j = 0;
        while (i < n) {
            if (s[i] == s[j]) dp[++i] = ++j;
            else if (j == 0) i++;
            else j = dp[j];
        }
        return dp[n] && dp[n] % (n - dp[n]) == 0;
    }
};
