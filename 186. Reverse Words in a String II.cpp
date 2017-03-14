/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

Related problem: Rotate Array
*/

// Same algorithm as 151. Reverse Words in a String, even simplier. Time: O(n), Space: O(1).
class Solution {
public:
    void reverseWords(string &s) {
        if (s.empty()) return;
        reverse(s.begin(), s.end());
        int i = 0;
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && !isblank(s[j])) j++;
            reverse(s.begin()+i, s.begin()+j);
            i = j+1;
        }
    }
};


// A more concise implementation:
class Solution {
public:
    void reverseWords(string &s) {
        if (s.empty()) return;
        reverse(s.begin(), s.end());
        for (int i = 0, j = 0; i < s.size(); i = j+1) {
            for (j = i; j < s.size() && !isblank(s[j]); j++);
            reverse(s.begin()+i, s.begin()+j);
        }
    }
};
