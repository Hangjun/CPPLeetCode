# Palindrome Substring Problems
[toc]

The key to solving palindrome substring problems is to make use of the **symmetry**.

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

[131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/#/description)
```
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.
For example, given s = "aab",
Return
[
  ["aa","b"],
  ["a","a","b"]
]
```

```c++
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        if (s.empty()) return res;
        vector<string> localSoln;
        int n = s.size();
        
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = n-1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                dp[i][j] = (j - i < 2 || dp[i+1][j-1]) && s[i] == s[j];
            }
        }
        
        dfs(s, 0, localSoln, res, dp);
        return res;
    }
    
    // dfs invariant: the substring before start is palindromic
    void dfs(string &s, int start, vector<string> &localSoln, vector<vector<string>> &res, vector<vector<bool>> &dp) {
        if (start == s.size()) {
            res.push_back(localSoln);
            return;
        }
        
        for (int i = start; i < s.size(); i++) {
            if (!dp[start][i]) continue;
            localSoln.push_back(s.substr(start, i-start+1));
            dfs(s, i+1, localSoln, res, dp);
            localSoln.pop_back();
        }
    }
};
```

[132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/#/description)
```
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.
For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
```

```c++
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
```

We can optimize the space utilization to $O(n)$. Here is the key idea: suppose we let $cut[i]$ to be the minimum number of cuts for the first i characters, i.e. the substring s[0,...,i-1]. Suppose that we are now at s[i], which is b. Its neighboring characters are s[0], s[0], ..., a, b, a, s[i+2],.... Since s[i-1, i, i+2] is palindromic, $cut[i+2]$ (min cuts for s[0,...,i+1]) is no greater than $cut[i-1] + 1$. 

This makes use of the symmetric property of palindromic strings. The case with even number of characters can be handled in a similar fashion.

```c++
// Time: O(n^2), Space: O(n)
class Solution {
public:
    int minCut(string s) {
        /* O(n^{2}) Time, O(n) Space */
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
```

[266. Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation/#/description)
```
Given a string, determine if a permutation of the string could form a palindrome.
For example,
"code" -> False, "aab" -> True, "carerac" -> True.
Hint:
1. Consider the palindromes of odd vs even length. What difference do you notice?
2. Count the frequency of each character.
If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?
```

```c++
class Solution {
public:
    bool canPermutePalindrome(string s) {
        bitset<256> ht;
        for (char c : s) ht.flip(c);
        return ht.count() < 2;
    }
};
```

[267. Palindrome Permutation II](https://leetcode.com/problems/palindrome-permutation-ii/#/description)
```
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.
For example:
Given s = "aabb", return ["abba", "baab"].
Given s = "abc", return [].
Hint:
1. If a palindromic permutation exists, we just need to generate the first half of the string.
2. To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.
```

```c++
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> res;
        unordered_map<char, int> ht;
        for (char c : s) ht[c]++;
        
        int odd = 0; char mid; string firstHalf;
        for (auto p : ht) {
            if (p.second % 2) {
                mid = p.first;
                if (++odd > 1) return res;
            }
            firstHalf += string(p.second / 2, p.first);
        }
        
        // generate all permutations of the first half
        string localSoln = "";
        vector<bool> canUse(firstHalf.size(), true);
        permuteDFS(firstHalf, canUse, localSoln, res);
        
        for (string &str : res) {
            string t(str);
            reverse(t.begin(), t.end());
            if (odd) t = mid + t;
            str += t;
        }
        
        return res;
    }
    
    void permuteDFS(string &firstHalf, vector<bool> &canUse, string &localSoln, vector<string> &res) {
        if (localSoln.size() == firstHalf.size()) {
            res.push_back(localSoln);
            return;
        }
        
        for (int i = 0; i < firstHalf.size(); i++) {
            if ((i > 0 && firstHalf[i] == firstHalf[i-1]) && canUse[i-1] || !canUse[i]) continue;
            canUse[i] = false;
            localSoln.push_back(firstHalf[i]);
            permuteDFS(firstHalf, canUse, localSoln, res);
            localSoln.pop_back();
            canUse[i] = true;
        }
    }
};
```



