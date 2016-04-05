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

/* Solution #1:
Time: O(n^2)
Space: O(1)
*/

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if (n <= 1)  return s;
        int lpsLen = prefixLPSLength(s);
        if (lpsLen == s.size()) // s is palindromic
            return s;
        string prefix = s.substr(lpsLen, n-lpsLen);
        reverse(prefix.begin(), prefix.end());
        return prefix+s;
    }
    
    int prefixLPSLength(string s) {
        // greedy search
        int n = s.size();
        int j = n;
        while (j > 1) {
            // test if size-j substring is palindromic
            if (validPalindrome(s.substr(0, j)))
                return j;
            else
                j--;
        }
        // j == 1
        return j;
    }

    bool validPalindrome(string s) {
        if (s.empty())  return true;
        int n = s.size();
        int i = 0, j = n-1;
        while (i<j) {
            if (s[i] == s[j]) {
                i++;
                j--;
            } else
                break;
        }
        if (i < j)
            return false;
        else 
            return true;
    }
};

/* Analysis:
Can we find the LPS prefix faster than O(n2) time? The idea is to use KMP algorithm. This is what we do: we reverse a copy of the input 
string, and concatenate it at the end of the original string. Then we search in the combined string the longest prefix that is also a 
suffix. This substring is then a LPS prefix in the original string. To compute this substring, we use KMP algorithm and compute the next 
table.
For references see: https://github.com/HaochenLiu/My-LeetCode/blob/master/214-1. cpp.
*/

/* Solution #2:
Time: O(n)
Space: O(1)
*/

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if (n <= 1)  return s;
        string combineReverse = preProcessing(s);
        int lpsLen = preFixLPS(combineReverse)+1;
        if (lpsLen == s.size()) // s is palindromic
            return s;
        string prefix = s.substr(lpsLen, n-lpsLen);
        reverse(prefix.begin(), prefix.end());
        return prefix+s;
    }
    
    string preProcessing(string s) {
        // s+#+reverse(s)
        string t = s.substr(0, s.size());
        reverse(t.begin(), t.end());
        return s+"#"+t;
    }
    
    int preFixLPS(string s) {
        int n = s.size();
        vector<int>next(n, -1);
        int j = -1;
        for (int i = 1; i < n; i++) {
            while (j >= 0 && s[i] != s[j+1]) j = next[j];
            if (s[i] == s[j+1]) j++;
            next[i] = j;
        }
        return next[n-1];
    }
};
