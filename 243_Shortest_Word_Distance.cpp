/*
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
*/

// Single pass: O(n) time, O(1) space

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int res = words.size();
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) pos1 = i;
            else if (words[i] == word2) pos2 = i;
            
            if (pos1 != -1 && pos2 != -1) res = min(res, abs(pos1 - pos2));
        }
        
        return res;
    }
};
