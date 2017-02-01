/*
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
*/

// Solution #1: Two traverals using hash table:

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> ht;
        for (int i = 0; i < s.size(); i++) {
            ht[s[i]]++;
        }
        
        for (int j = 0; j < s.size(); j++) {
            if (ht[s[j]] == 1) return j;
        }
        
        return -1;
    }
};

// Solution #2: We can always use a vector instead of a hash table since all characters are lower case alphabets.
class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> ht(26, 0);
        
        for (int i = 0; i < s.size(); i++) {
            ht[s[i] - 'a']++;
        }
        
        for (int j = 0; j < s.size(); j++) {
            if (ht[s[j] - 'a'] == 1) return j;
        }
        
        return -1;
    }
};

// Solution #3: If the string is very large, and consists of lots of repeating characters, we do not want to traverse the string twice. Instead, we can store the indices in the hash table as well, and only traverse the hash table the second time.
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, pair<int, int>> ht;
        int res = s.size();
        
        for (int i = 0; i < s.size(); i++) {
            ht[s[i]].first++;
            ht[s[i]].second = i;
        }
        
        for (auto &p : ht) {
            // p is an element of ht. p.second is the pair<int, int>.
            if (p.second.first == 1) res = min(res, p.second.second);
        }
        
        return res == s.size() ? -1 : res;
    }
};

/*
Two remarks about the last solution:
1. The result needs to be initialized to s.size().
2. When using auto &p : ht, p is an element of ht, and p.first is the char part of the hash table; p.second is the pair<int, int> part of the hash table.
*/
