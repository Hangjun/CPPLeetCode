/*
Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.
Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]
*/

// Time: O(n), Space: O(1).
class Solution {
public:
    string reverseStr(string s, int k) {
        int i = 0;
        int n = s.size();
        while (i < n) {
            int j = min(i+k-1, n-1);
            reverse(s, i, j);
            i += 2 * k;
        }
        return s;
    }
    
    void reverse(string &s, int start, int end) {
        while (start < end) swap(s[start++], s[end--]);
    }
};
