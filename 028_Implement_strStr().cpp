/*
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/

// Straightforward Solution: Time O(mn)
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        if (needle.empty()) return 0;
        
        int m = haystack.size();
        int n = needle.size();
        
        for (int i = 0; i <= m-n; i++) {
            for (int j = 0; j <= n; j++) {
                if (j == n) return i;
                if (haystack[i+j] != needle[j]) break;
            }
        }
        
        return -1;
    }
};


// KMP solution: Time = O(m+n); Space = O(n).
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        if (needle.empty()) return 0;
        
        int m = haystack.size();
        int n = needle.size();
        vector<int> next(n, -1);
        nextTable(needle, next);
        
        int j = -1;
        for (int i = 0; i < m; i++) {
            while (j >= 0 && haystack[i] != needle[j+1]) j = next[j];
            if (haystack[i] == needle[j+1]) j++;
            if (j == n-1) return i-n+1;
        }
        
        return -1;
    }
    
    void nextTable(string needle, vector<int> &next) {
        int j = -1;
        for (int i = 1; i < needle.size(); i++) {
            while (j >= 0 && needle[i] != needle[j+1]) j = next[j];
            if (needle[i] == needle[j+1]) j++;
            next[i] = j;
        }
    }
};
