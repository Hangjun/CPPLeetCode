/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
*/

/* Analysis:
If we can find the longest palindromic substring (LPS) that begins with the first character of the given string, the additional length 
needed is simply the total length of the string minus the length of that LPS. Thus the key is to find the LPS. One straightforward 
algorithm runs in O(n^2) time.
*/

/* Solution #1: Time Limit Exceeded.
Time: O(n^2)
Space: O(1)
*/

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if (n <= 1)  return s;
        int lpsLen = prefixLPSLength(s);
        // s is palindromic
        if (lpsLen == n return s;
        string prefix = s.substr(lpsLen, n - lpsLen);
        reverse(prefix.begin(), prefix.end());
        return prefix + s;
    }
    
    int prefixLPSLength(string s) {
        // greedy search for palindrome prefix of size j
        int j = s.size();
        while (j >= 1) {
            // test if size-j substring is palindromic
            if (validPalindrome(s.substr(0, j))) return j;
            j--;
        }
    }

    bool validPalindrome(string s) {
        if (s.empty() || s.size() == 1)  return true;
        int i = 0, j = s.size() - 1;
        while (i < j && s[i] == s[j]) {
                i++;
                j--;
        }
        return i >= j;
    }
};

/* Analysis:
Can we find the LPS prefix faster than O(n2) time? The idea is to use KMP algorithm. This is what we do: we reverse a copy of 
the input string, and concatenate it at the end of the original string. Then we search in the combined string the longest 
prefix that is also a suffix. This substring is then a LPS prefix in the original string. To compute this substring, we use 
KMP algorithm and compute the next table.

The next table is the most important data structure for all the palindromic substring problems.

For references see: https://github.com/HaochenLiu/My-LeetCode/blob/master/214-1. cpp.

KMP next table: Time: O(n), Space: O(1).
*/
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
    
    // Just memorize the next table construction. If you can memorize it, that means you already understand it.
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

/*
Remark: There are a couple different next table constructions with the same idea but different implementations. We will stick to this implementation for all the LPS problems.
*/
