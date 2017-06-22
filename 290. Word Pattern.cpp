/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
*/

// Time: O(n), Space: O(n). Two hash tables.
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> p2w;
        unordered_map<string, char> w2p;
        istringstream in(str);
        string word;
        vector<string> vs;
        while (in >> word) vs.push_back(word); 
        if (vs.size() != pattern.size()) return false;

        for (int i = 0; i < vs.size(); i++) {
            char p = pattern[i];
            string word = vs[i];
            if (p2w.find(p) == p2w.end()) {
                p2w[p] = word;
            } else if (p2w[p] != word) {
                return false;
            }
            
            if (w2p.find(word) == w2p.end()) {
                w2p[word] = p;
            } else if (w2p[word] != p) {
                return false;
            }
        }
        return true;
    }
};
