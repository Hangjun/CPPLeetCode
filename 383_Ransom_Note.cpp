/*
Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
*/

// Time = O(n), Space = O(1)
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> magazineTable(128, 0);
        for (char m : magazine) magazineTable[m]++;
        for (char n : ransomNote) {
            if (--magazineTable[n] < 0) return false;
        }
        return true;
    }
};
