/*
Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

Example

Given the string = "abcdzdcab", return "cdzdc".
Challenge

O(n2) time is acceptable. Can you do it in O(n) time.
*/

/* 
DP Solution. Time: O(n^2), Space: O(n^2).
*/
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        int n = s.size();
        int maxLen = 0;
        int start = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        // This is the joseki for computing whether any substring s[i...j] is palindromic. Memorize it!
        for (int i = n-1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if ((j - i < 2 || dp[i+1][j-1]) && s[i] == s[j]) {
                    dp[i][j] = true; // this also includes the initial state of dp[i][i] being true, for all i
                    if (j - i + 1 > maxLen) {
                        maxLen = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
};

/*
The second algorithm takes constant space. The idea is to, for every character in the string, check how long a palindromic substring can it expand to with it being its center. What is the total number of such centers given that there are n characters in the string? The answer is 2n+1, not n, since there is a possible center between any two consecutive characters (think about the case where a palindromic subtring has even number of characters).

Time: O(n^2), Space: O(1).
*/
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        int n = s.size();
        string res;
        for (int i = 0; i < n; i++) {
            string odd = expand(s, i, i);
            if (odd.size() > res.size()) res = odd;
            
            string even = expand(s, i, i+1);
            if (even.size() > res.size()) res = even;
        }
        
        return res;
    }
    
    string expand(string &s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return s.substr(left+1, right-left-1);
    }
};

/*
This is still not the optimal solution. It is quite obvious that we are re-computing a lot of the overlapping substrings for two centers in the above expansion algorithm. The optimal solution in fact takes O(n) time, and O(n) space, and is called the Manachers Algorithm.

The basic idea is that if we need to calculate Longest Palindromic Substring at each 2n+1 positions from left to right, then palindrome’s symmetric property could help to avoid some of the unnecessary computations (i.e. character comparison). If there is a palindrome of some length L cantered at any position P, then we may not need to compare all characters in left and right side at position P+1. We already calculated LPS at positions before P and they can help to avoid some of the comparisons after position P.

See this post for a detailed explaination: http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/.

Manachers Algorithm: Time: O(n), Space: O(n).
*/
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        string t = preprocess(s);
        int n = t.size();
        int centerIndex = 0;
        int maxLen = 0;
        vector<int> dp(n, 0); // dp[i] = longest palindrome substring centered at index i
        int center = 0, right = 0;
        
        for (int i = 1; i < n-1; i++) {
            int iMirror = center - (i - center);
            dp[i] = (right > i) ? min(right - i, dp[iMirror]) : 0;
            
            // try to expand centered at s[i]
            while (t[i+dp[i]+1] == t[i-dp[i]-1]) ++dp[i];
            if (i+dp[i] > right) {
                right = i + dp[i];
                center = i;
            }
            
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                centerIndex = i;
            }
        }
        
        return s.substr((centerIndex-maxLen-1)/2, maxLen);
    }
    
    string preprocess(string s) {
        // ˆ and $ are sentinels appended to each end to avoid bounds checking
        string t = "^";
        for (int i = 0; i < s.size(); i++) {
            t += "#" + s.substr(i, 1);
        }
        t += "#$";
        return t;
    }
};
