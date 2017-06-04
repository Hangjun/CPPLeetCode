/*
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"
*/

/*
Analysis: This is really not a hard problem. It is trivial to dedup: we use a visited a table to keep track of the characters to be included into the final result. The slightly tricky part here is to maintain minimal in lexicographical order.

When can we be sure that it is safe to replace a previously included character by the current character in order to maintain minimal? We can be sure if we know that there is another such character in later part of the string. How do we know that? We use a histogram table to record the frequencies of all the characters. 

Therefore, the key logic becomes: whenever we include a character into the final result, we mark it as visitied; for each new character (non-visited), we check if it can replace the previously included characters.

Time: O(n), Space: O(1). 2 Passes.
*/

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> hist(256, 0);
        vector<bool> visited(256, false);
        string res = "";
        
        for (char c : s) ++hist[c - 'a'];
        
        for (char c : s) {
            --hist[c - 'a'];
            if (visited[c]) continue;
            while (!res.empty() && c < res.back() && hist[res.back() - 'a']) {
                // if we still have res.back() it is save (and necessary) to kick the last character to maintain minimal
                visited[res.back()] = false;
                res.pop_back();
            }
            res.push_back(c);
            visited[c] = true;
        }
        
        return res;
    }
};
