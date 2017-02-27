/*
This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.

Note:
You may assume word1 and word2 are both in the list.
*/

class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int res = words.size();
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                pos1 = i;
            }
            if (words[i] == word2) {
                if (word1 == word2) pos1 = pos2;
                pos2 = i;
            }
            if (pos1 != -1 && pos2 != -1) res = min(res, abs(pos1 - pos2));
        }
        return res;
    }
};
