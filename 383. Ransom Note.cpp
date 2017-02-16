/*
Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
*/

// Time O(m+n), Space O(1) where m = ransomNote.size(), n = magazine.size()
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (magazine.empty()) return ransomNote.empty();
        vector<int> count(256, 0);
        for (char c : magazine) count[c - 'a']++;
        for (char c : ransomNote) {
            if (--count[c - 'a'] < 0) return false;
        }
        return true;
    }
};
