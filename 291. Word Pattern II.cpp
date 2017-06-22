/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:
pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false.
Notes:
You may assume both pattern and str contains only lowercase letters.
*/

class Solution {
public:
    unordered_map<char, string> p2w;
    unordered_map<string, char> w2p;
    
    bool wordPatternMatch(string pattern, string str) {
        return match(pattern, 0, str, 0);
    }
    
    bool match(string &pattern, int i, string &str, int j) {
        int m = pattern.size(), n = str.size();
        if (i == m && j == n) {
            return true;
        } else if (i == m || j == n) {
            return false;
        }
        
        bool pairFound = false;
        for (int k = j; k < n; k++) {
            string word = str.substr(j, k-j+1);
            char p = pattern[i];
            
            if (p2w.find(p) != p2w.end()) {
                if (p2w[p] != word) continue;
            } else if (w2p.find(word) != w2p.end()) {
                if (w2p[word] != p) continue;
            } else {
                p2w[p] = word;
                w2p[word] = p;
                pairFound = true;
            }
            
            // DFS
            if (match(pattern, i+1, str, k+1)) return true;
            
            // backtrack
            if (pairFound) {
                p2w.erase(p);
                w2p.erase(word);
            }
        }
        
        return false;
    }
};
