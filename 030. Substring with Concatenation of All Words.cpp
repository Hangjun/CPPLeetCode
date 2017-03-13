/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

/*
Analysis: This problem is identical to 28. Implement strStr(). We use two pointers, one traverses the global string s, and the other traverse the list of words that need to be matched. We also maintain two hash table to keep track of expected words and words seen so far, respectively. 

Time: O(nm), Space: O(n + m). n = s.size(), m = total size of words need to find = words.size() * length of each word.
*/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int n = s.size(), num = words.size(), len = words[0].size();
        if (n < num * len) return res;
        unordered_map<string, int> need;
        for (string s : words) need[s]++;
        
        for (int i = 0; i < n - num * len + 1; i++) {
            int j = 0;
            unordered_map<string, int> seen;
            for (; j < num; j++) {
                string cur = s.substr(i+j*len, len);
                if (need.find(cur) == need.end() || ++seen[cur] > need[cur]) break;
            }
            if (j == num) res.push_back(i);
        }
        return res;
    }
};
