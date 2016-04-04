/*
 Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.
Clarification:

    What constitutes a word?
    A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
    Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
    Reduce them to a single space in the reversed string.
*/

class Solution {
public:
    void reverseWords(string &s) {
        if (s.empty()) return;
        // trim
        vector<string> res;
        int i = 0, j = s.size();
        while (i < j && isspace(s[i])) i++;
        while (j > i && isspace(s[j-1])) j--;
        while (i < j) {
            int start = i;
            if (!isspace(s[start])) {
                // move i to the first space character
                while (i < j && !isspace(s[i])) i++;
                // push the word s[start,...,i] into res
                res.push_back(s.substr(start, i-start));
            } else {
                // move i to the first non-space character
                while (i < j && isspace(s[i])) i++;
                res.push_back(" ");
            }
        }
        reverse(res.begin(), res.end());
        s = "";
        for (int k = 0; k < res.size(); k++) {
            s += res[k];
        }
    }
};
