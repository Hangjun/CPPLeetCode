/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

/* Analysis:
String matching problems usually admit a dynamic programming solution. The difficulty of this problem lies in the handling of '*'.
*/
// Dynamic Programming solution
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size();
        int n = p.size();
        // dp[i][j] = isMatch(s[0,...,i-1], p[0,...,j-1])
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) { // do not care empty pattern
                if (p[j-1] != '.' && p[j-1] != '*') {
                    dp[i][j] = i > 0 && p[j-1] == s[i-1] && dp[i-1][j-1];
                } else if (p[j-1] == '.') {
                    dp[i][j] = i > 0 && dp[i-1][j-1];
                } else { // p[j-1] == '*'
                    assert(j > 1); // cannot be the first character
                    // dp[i][j] = match 0 or 1 or more of the previous character
                    dp[i][j] = (dp[i][j-2] || dp[i][j-1] || (i > 0 && (p[j-2] == s[i-1] || p[j-2] == '.') && dp[i-1][j]));
                }
            }
        }
        return dp[m][n];
    }
};


/* Analysis: There is a beautiful article on this problem from the official LeetCode website. We follow the solution provided therein.

It seems that some readers are confused about why the regex pattern “.*” matches the string “ab”. “.*” means repeat the preceding element 0 or more times. Here, the “preceding” element is the dot character in the pattern, which can match any characters. Therefore, the regex pattern “.*” allows the dot to be repeated any number of times, which matches any string (even an empty string).

Hints:
Think carefully how you would do matching of ‘*’. Please note that ‘*’ in regular expression is different from wildcard matching, as we match the previous character 0 or more times. But, how many times? If you are stuck, recursion is your friend.

This problem is a tricky one. Due to the huge number of edge cases, many people would write lengthy code and have numerous bugs on their first try. Try your best getting your code correct first, then refactor mercilessly to as clean and concise as possible!


A sample diagram of a deterministic finite state automata (DFA). DFAs are useful for doing lexical analysis and pattern matching. An example is UNIX’s grep tool. Please note that this post does not attempt to descibe a solution using DFA.

Solution:
This looks just like a straight forward string matching, isn’t it? Couldn’t we just match the pattern and the input string character by character? The question is, how to match a ‘*’?

A natural way is to use a greedy approach; that is, we attempt to match the previous character as many as we can. Does this work? Let us look at some examples.

s = “abbbc”, p = “ab*c”
Assume we have matched the first ‘a’ on both s and p. When we see “b*” in p, we skip all b’s in s. Since the last ‘c’ matches on both side, they both match.

s = “ac”, p = “ab*c”
After the first ‘a’, we see that there is no b’s to skip for “b*”. We match the last ‘c’ on both side and conclude that they both match.

It seems that being greedy is good. But how about this case?

s = “abbc”, p = “ab*bbc”
When we see “b*” in p, we would have skip all b’s in s. They both should match, but we have no more b’s to match. Therefore, the greedy approach fails in the above case.

One might be tempted to think of a quick workaround. How about counting the number of consecutive b’s in s? If it is smaller or equal to the number of consecutive b’s after “b*” in p, we conclude they both match and continue from there. For the opposite, we conclude there is not a match.

This seem to solve the above problem, but how about this case:
s = “abcbcd”, p = “a.*c.*d”

Here, “.*” in p means repeat ‘.’ 0 or more times. Since ‘.’ can match any character, it is not clear how many times ‘.’ should be repeated. Should the ‘c’ in p matches the first or second ‘c’ in s? Unfortunately, there is no way to tell without using some kind of exhaustive search.

We need some kind of backtracking mechanism such that when a matching fails, we return to the last successful matching state and attempt to match more characters in s with ‘*’. This approach leads naturally to recursion.

The recursion mainly breaks down elegantly to the following two cases:

    If the next character of p is NOT ‘*’, then it must match the current character of s. Continue pattern matching with the next character of both s and p.
    If the next character of p is ‘*’, then we do a brute force exhaustive matching of 0, 1, or more repeats of current character of p… Until we could not match any more characters.

You would need to consider the base case carefully too. That would be left as an exercise to the reader. :)
*/

// Recursive solution
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size(), n = p.size();
        int i = 0, j = 0;
        
        if (p[j+1] != '*') { // p's next character is not '*'
            assert(p[j] != '*');
            return ((p[j] == s[j] || (p[j] == '.' && i < m)) && isMatch(s.substr(i+1), p.substr(j+1)));
        }
        // p's next character is '*'
        while (p[j] == s[i] || (p[j] == '.' && i < m)) {
            if (isMatch(s.substr(i), p.substr(j+2))) {
                return true;
            }
            i++;
        }
        return isMatch(s.substr(i), p.substr(j+2));
    }
};


