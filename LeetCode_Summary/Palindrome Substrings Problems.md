# Palindrome Substring Problems

[5. Longest Palindromic Substring Add to List
](https://leetcode.com/problems/longest-palindromic-substring/#/description)

```
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
Example:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example:
Input: "cbbd"
Output: "bb"
```

```c++
// DP Solution. Time: O(n^2), Space: O(n^2).
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
```

The second algorithm takes constant space. The idea is to, for every character in the string, check how long a palindromic substring can it expand to with it being its center. What is the total number of such centers given that there are n characters in the string? The answer is 2n+1, not n, since there is a possible center between any two consecutive characters (think about the case where a palindromic substring has even number of characters).

```c++
// Time: O(n^2), Space: O(1).
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
```

This is still not the optimal solution. It is quite obvious that we are re-computing a lot of the overlapping substrings for two centers in the above expansion algorithm. The optimal solution in fact takes O(n) time, and O(n) space, and is called the **Manachers Algorithm**.

The basic idea is that if we need to calculate Longest Palindromic Substring at each $2n+1$ positions from left to right, then palindrome’s symmetric property could help to avoid some of the unnecessary computations (i.e. character comparison). If there is a palindrome of some length L cantered at any position P, then we may not need to compare all characters in left and right side at position P+1. We already calculated LPS at positions before P and they can help to avoid some of the comparisons after position P.

See this post for a detailed explaination: http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/.

```c++
// Manachers Algorithm: Time: O(n), Space: O(n).
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
```

_Remark_: We also want to point out that the DP computation in the first algorithm (that finds for every pair of indices $i$, $j$, whether the substring $s[i...j]$ is palindromic) is the **joseki** DP for palindromic substring computations. Every time we need to be able to query such a pair of indices and get a result, this exact DP computation should be used without any change.

[214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/#/description)
```
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".
```

The first idea is that, if we can find the longest palindromic prefix, the result of this problem is then the concatenation of the reverse of the remaining suffix (the input string minus the longest palindromic prefix) and the input string itself. How do we find the longest palindromic prefix? The straightforward to algorithm is search from index n-1 to 1, n being the length of the input string, and find the first index i such that the substring from 0 to i is a palindromic. This takes $O(n^2)$ time.

Can we find the LPS prefix faster than $O(n^2)$ time? The idea is to use the **KMP algorithm**. This is what we do: we reverse a copy of the input string, and concatenate it at the end of the original string. Then we search in the combined string the longest prefix that is also a suffix. This substring is then a LPS prefix in the original string. To compute this substring, we use KMP algorithm and compute the next table.

_Remark_: The next table is the most important data structure for all the palindromic substring problems. There are a couple different next table constructions with the same idea but different implementations. We will stick to this implementation for all the LPS problems.

```c++
// KMP next table: Time: O(n), Space: O(1).
class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.size() <= 1) return s;
        int n = s.size();
        string t = s;
        reverse(t.begin(), t.end());
        int palPrefixLength = prefixLPS(s + "#" + t);
        if (palPrefixLength == n) return s;
        string suffix = s.substr(palPrefixLength, n-palPrefixLength);
        reverse(suffix.begin(), suffix.end());
        return suffix + s;
    }
    
    int prefixLPS(string s) {
        int n = s.size();
        vector<int> next(n, -1);
        int j = -1;
        
        for (int i = 1; i < n; i++) {
            while (j >= 0 && s[i] != s[j+1]) j = next[j];
            if (s[i] == s[j+1]) next[i] = ++j;
        }
        
        return next[n-1] + 1;
    }
};
```

Now that we learned the construction of the next table, let's solve the classic problem that uses it:

[28. Implement strStr()](https://leetcode.com/problems/implement-strstr/#/description) ([Github Solution](https://leetcode.com/problems/implement-strstr/#/description))
```
Implement strStr().
Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
```

The two pointer solution takes $O(mn)$ time. The KMP algorithm takes $O(m+n)$ time but uses $O(n)$ space to store the next table. Here $m$ is the length of the haystack, and $n$ is the length of the needle. Therefore the space complexity is really not that high.

```c++
// KMP with next table. Time: O(m+n), Space: O(n).
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        if (needle.empty()) return 0;
        int m = haystack.size(), n = needle.size();
        vector<int> next(n, -1);
        nextTable(needle, next);
        
        int j = -1;
        for (int i = 0; i < m; i++) {
            while (j >= 0 && haystack[i] != needle[j+1]) j = next[j];
            if (haystack[i] == needle[j+1]) j++;
            if (j == n-1) return i-n+1;
        }
        
        return -1;
    }
    
    void nextTable(string s, vector<int> &next) {
        int j = -1;
        for (int i = 1; i < s.size(); i++) {
            while (j >= 0 && s[i] != s[j+1]) j = next[j];
            if (s[i] == s[j+1]) next[i] = ++j;
        }
    }
    
};
```


