Write a function to find the longest common prefix string amongst an array of strings. 


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0)  return "";
        if (n == 1)  return strs[0];
        string lcp = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            lcp = commonSubstr(lcp, strs[i]);
        }
        return lcp;
    }
    
    string commonSubstr(string s1, string s2){
        int n = min(s1.size(), s2.size());
        for (int i = 0; i < n; i++) {
            if (s1[i] != s2[i])  return s1.substr(0, i);
        }
        return s1.substr(0, n);
    }
};
