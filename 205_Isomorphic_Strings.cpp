/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // corner cases:
        if (s.size() != t.size()) return false;
        // establish a bidirectional hash table mapping
        // mapping should be 1 - 1
        unordered_map<char, char> forward;
        unordered_map<char, char> backward;
        for (int i = 0; i < s.size(); i++) {
            if (forward.find(s[i]) == forward.end()) {
                forward[s[i]] = t[i];
            } else if (forward[s[i]] != t[i]) {
                return false;
            }
            
            if (backward.find(t[i]) == backward.end()) {
                backward[t[i]] = s[i];
            } else if (backward[t[i]] != s[i]) {
                return false;
            }
        }
        return true;
    }
};

// More concisely:

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size())  return false;
        unordered_map<char, char> m1, m2;
        for (int i = 0; i < s.size(); i++) {
            if (m1.find(s[i]) == m1.end() && m2.find(t[i]) == m2.end()) {
                m1[s[i]] = t[i];
                m2[t[i]] = s[i];
            } else {
                if (m1[s[i]] != t[i] || m2[t[i]] != s[i])
                    return false;
            }    
        }
        return true;
    }+
};

// Solution #3: Without using hash table.
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) return false;
        vector<int> map_s(128, 0);
        vector<int> map_t(128, 0);
        int len = s.size();
        for (int i = 0; i < len; i++) {
            if (map_s[s[i]] != map_t[t[i]]) return false;
            map_s[s[i]] = i+1;
            map_t[t[i]] = i+1;
        }
        
        return true;
    }
};
