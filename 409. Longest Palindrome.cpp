/*
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/

class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> count(256, 0);
        for (char c : s) count[c - '0']++;
        int res = 0;
        for (int n : count) res += n % 2 ? (res % 2 ? n-1 : n) : n;
        return res;
    }
};
