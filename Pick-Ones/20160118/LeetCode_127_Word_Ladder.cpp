/*
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the word list

For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.
*/

/* Submission #1: BFS: Failed
"a"
"c"
["a","b","c"]
Output: 3
Expected: 2 
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        if (beginWord == endWord) return 1;
        if (wordList.empty()) return 0;
        wordList.insert(endWord);
        queue<string> q;
        q.push(beginWord);
        // initialize distance to be 1
        int dist = 1; 
        while (!q.empty()) {
            string curWord = q.front();
            q.pop();
            if (curWord == endWord) {
                return dist;
            }
            // search all words that are 1 distance away from curWord
            getNextLevel(wordList, curWord, q);
            dist++;
        }
        return 0;
    }
    
private:
    void getNextLevel(unordered_set<string> &wordList, string curWord, queue<string> &q) {
        for (int i = 0; i < curWord.size(); i++) {
            char c = curWord[i];
            // substitute c with 'a' through 'z'
            for (char j = 'a'; j <= 'z'; j++) {
                if(j == c) continue;
                curWord[i] = j;
                if (wordList.find(curWord) != wordList.end()) {
                    q.push(curWord);
                    // remove curWord so not to visit it again
                    wordList.erase(curWord);
                }
                curWord[i] = c;
            }
        }
    }
};

/* Analysis:
For each level, there might be many words. Therefore we cannot just a single queue if we want to do this in a strict level-by-level order. 
*/

// Submission #2: BFS with two queues: Accepted
class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        if (beginWord == endWord) return 1;
        if (wordList.empty()) return 0;
        wordList.insert(endWord);
        queue<string> curLevel;
        queue<string> nextLevel;
        curLevel.push(beginWord);
        // initialize distance to be 1
        int dist = 1; 
        while (!curLevel.empty()) {
            while (!curLevel.empty()) {
                string curWord = curLevel.front();
                curLevel.pop();
                if (curWord == endWord) {
                    return dist;
                }
                // search all words that are 1 distance away from curWord
                getNextLevel(wordList, curWord, nextLevel);
            }
            swap(curLevel, nextLevel);
            dist++;
        }
        return 0;
    }
    
private:
    void getNextLevel(unordered_set<string> &wordList, string curWord, queue<string> &q) {
        for (int i = 0; i < curWord.size(); i++) {
            char c = curWord[i];
            // substitute c with 'a' through 'z'
            for (char j = 'a'; j <= 'z'; j++) {
                if(j == c) continue;
                curWord[i] = j;
                if (wordList.find(curWord) != wordList.end()) {
                    q.push(curWord);
                    // remove curWord so not to visit it again
                    wordList.erase(curWord);
                }
                curWord[i] = c;
            }
        }
    }
};

/* Analysis: 
We can use a single queue if we also keep track of the distance of each word from  beginWord.
*/

// Submission #3: Accepted

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        if (beginWord == endWord) return 1;
        if (wordList.empty()) return 0;
        wordList.insert(endWord);
        queue<pair<string, int>> q;
        q.push(make_pair(beginWord, 1));
        while (!q.empty()) {
            pair<string, int> curWord = q.front();
            q.pop();
            if (curWord.first == endWord) {
                return curWord.second;
            }
            vector<string> neighbors;
            bfs(wordList, curWord.first, neighbors);
            for (int i = 0; i < neighbors.size(); i++) {
                q.push(make_pair(neighbors[i], curWord.second+1));
            }
        }
        return 0;
    }
    
    void bfs(unordered_set<string> &wordList, string curWord, vector<string> &neighbors) {
        for (int i = 0; i < curWord.size(); i++) {
            char c = curWord[i];
            for (char j = 'a'; j <= 'z'; j++) {
                if (j == c) continue;
                curWord[i] = j;
                if (wordList.find(curWord) != wordList.end()) {
                    wordList.erase(curWord);
                    neighbors.push_back(curWord);
                }
                curWord[i] = c;
            }
        }
    }
};
