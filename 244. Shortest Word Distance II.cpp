/*
This is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?

Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
*/

// Time: O(n), Space: O(n)
class WordDistance {
public:
    WordDistance(vector<string> words) {
        for (int i = 0; i < words.size(); i++) {
            ht[words[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        int i = 0, j = 0;
        vector<int> index1 = ht[word1];
        vector<int> index2 = ht[word2];
        int res = INT_MAX;
        while (i < index1.size() && j < index2.size()) {
            res = min(res, abs(index1[i] - index2[j]));
            if (index1[i] < index2[j]) i++;
            else j++;
        }
        return res;
    }
private:
    unordered_map<string, vector<int>> ht; // string->indices
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(words);
 * int param_1 = obj.shortest(word1,word2);
 */
