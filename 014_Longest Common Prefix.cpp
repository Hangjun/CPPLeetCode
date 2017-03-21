/*
Write a function to find the longest common prefix string amongst an array of strings. 
*/

/*
Analysis: The first idea is to compute the minimum length of all the strings first, and then traverse the strs to compute the lcp one character at a time. Let n be the common minimum length, and m be the total number of strings. Then the algorithm takes O(m*n) time. We can also do this constructively and find the lcp with 2 strings at a time.
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        int n = strs.size();
        string lcp = strs[0];
        for (int i = 1; i < n; i++) {
            findLCP(lcp, strs[i]);
        }
        return lcp;
    }
    
    void findLCP(string &lcp, string s) {
        int n = min(lcp.size(), s.size());
        int i = 0;
        while (i < n && lcp[i] == s[i]) i++;

        lcp = lcp.substr(0, i);
    }
};
