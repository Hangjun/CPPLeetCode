/* Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

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


This is similar to finding the shortest path between two nodes in a graph, and here a node is a string, and there is an edge
between two strings if and only if they differ by only one character, and they both exist in the \verb+wordList+. 

To find the shortest path, we use BFS. There are three main components of the solution via BFS:
1. Given a string, how to find its neighboring strings?
2. How to make sure we don't visit a visited node?
3. How to backtrack to print out the shortest path?

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        // corner case
        if (beginWord == endWord) return 1;
        if (wordList.empty()) return 0;
        if (beginWord.size() != endWord.size()) return 0;
        wordList.insert(endWord);
        queue<pair<string, int>> q;
        q.push(make_pair(beginWord, 1));
        while (!q.empty()) {
            string curWord = q.front().first;
            int len = q.front().second;
            q.pop();
            if (curWord == endWord) {
                return len;
            }
            // BFS on neighboring strings of curWord
            vector<string> neighbors = findNeighbors(curWord, wordList);
            for (int i = 0; i < neighbors.size(); i++) {
                q.push(make_pair(neighbors[i], len+1));
            }
        }
        return 0;
    }
    
    vector<string> findNeighbors(string curWord, unordered_set<string> &wordList) {
        vector<string> neighbors;
        for (int i = 0; i < curWord.size(); i++) {
            // change one character at a time
            for (char j = 'a'; j <= 'z'; j++) {
                char c = curWord[i];
                if (c == j) continue;
                curWord[i] = j;
                if (wordList.count(curWord)) {
                    neighbors.push_back(curWord);
                    wordList.erase(curWord); // provides a visited mechnism
                }
                // reset ith character
                curWord[i] = c;
            }
        }
        return neighbors;
    }
};


Notice that on Line 67 above, once we find a legitimate neighbor word, we erase it from the dictionary. This severs the same purpose as a visited array. Now why can we erase this word? To justify this, there are two cases: 

1. First, this word won't be reached on a later traversal. In this case we can certainly erase it from the dictionary.
2. Second, this word will be reached on this level's traversal or at a later level. If we will reach this word again on the current level, that means there are at least two ways to reach this word, and they all take the same number of steps (this is what reaching this word again on the current level means). Erasing this word won't change the output answer since it is already covered.

If, on the other hand, this word will be reached at a later traversal. That means that keeping this word won't provide a better solution, since we are only looking for the shortest length here. 

However, if we were to print out all the minimal length paths or simply all paths from beginWord to endWord, we cannot simply erase any intermediate word.

We have mentioned that this problem is really finding the smallest path from one word to another, where each step is restricted to one edit distance away. If we want to clearly separate each level during our traversal, we can use two queues instead of one. This is very similar to the Binary Tree Level Order Traversal problem:

class Solution {
public:
    int ladderLength(string beginWord, string endWord,
    unordered_set<string>& wordList) {
        // corner case
        if (beginWord == endWord) return 1;
        if (wordList.empty()) return 0;
        if (beginWord.size() != endWord.size()) return 0;
        //wordList.insert(beginWord);
        wordList.insert(endWord); 
        int dist = 1;
        queue<string> curLevel;
        queue<string> nextLevel;
        curLevel.push(beginWord);
        while (!curLevel.empty()) {
            while (!curLevel.empty()) {
                string s = curLevel.front();
                curLevel.pop();
                if (s == endWord) {
                    return dist;
                }
                // find all words distance 1 away from s
                findNeighbors(s, wordList, nextLevel);
            }
            swap(curLevel, nextLevel);
            dist++;
        }
        return 0;
    }
    
    void findNeighbors(string s, unordered_set<string> &wordList,
    queue<string> &nextLevel) {
        for (int i = 0; i < s.size(); i++) {
            for (char j = 'a'; j <= 'z'; j++) {
                char c = s[i];
                if (j == c) continue;
                s[i] = j;
                if (wordList.count(s)) {
                    nextLevel.push(s);
                    // make sure you understand why we can erase s!!
                    wordList.erase(s);
                }
                s[i] = c;
            }
        }
    }
};
