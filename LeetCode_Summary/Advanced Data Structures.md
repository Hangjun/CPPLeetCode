# Advanced Data Structures
[toc]

[378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/#/description)
```
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element.
Example:
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,
return 13.
Note: 
You may assume k is always valid, 1 ≤ k ≤ n2.
```

```c++
class Cell {
public:
    int x;
    int y;
    int val;
   
    Cell(int _x = 0, int _y = 0, int _val = 0):x(_x), y(_y), val(_val) {}
    
    bool operator < (const Cell &c) const {
        return val > c.val;
    }
};

struct pair_hash {
    inline size_t operator()(const pair<int,int> &v) const {
        return v.first*31 + v.second;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if (matrix.empty() || matrix[0].empty()) return INT_MAX;
        int m = matrix.size(), n = matrix[0].size();
        if (k > m*n || k < 1) return INT_MAX;
        unordered_set<pair<int, int>, pair_hash> visited;
        priority_queue<Cell> minHeap;
        int count = 0;
        Cell c(0, 0, matrix[0][0]);
        visited.insert(make_pair(0, 0));
        minHeap.push(c);
        while (count < k-1) {
            Cell cur = minHeap.top();
            minHeap.pop();
            ++count;
            for (int i = 0; i < 2; i++) { // next bigger elements are on the right and bottom
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                pair<int, int> px = make_pair(nx, ny);
                if (!inBound(matrix, nx, ny) || visited.find(px) != visited.end()) continue;
                visited.insert(px);
                minHeap.push(Cell(nx, ny, matrix[nx][ny]));
            }
        }
        return minHeap.top().val;
    }
    
private:
    bool inBound(vector<vector<int>> &matrix, int x, int y) {
        int m = matrix.size();
        int n = matrix[0].size();
        return x >= 0 && x < m && y >= 0 && y < n;
    }
    int dx[2] = {1, 0};
    int dy[2] = {0, 1};
};
```

## Priority Queue / Heap

## Union-Find

## Red-Black Tree

## AVL Tree

## Trie (Prefix Tree)
[208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/#/description)
```
Implement a trie with insert, search, and startsWith methods.
Note:
You may assume that all inputs are consist of lowercase letters a-z.
```

```c++
class TrieNode {
public:
    TrieNode *ch[26];
    bool isEnd;
    
    TrieNode(): isEnd(false) {
        for (int i = 0; i < 26; i++) ch[i] = NULL;
    }
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            int j = word[i] - 'a';
            if (!p->ch[j]) p->ch[j] = new TrieNode(); // create child node if child j does not exist
            p = p->ch[j];
        }
        p->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            int j = word[i] - 'a';
            if (!p->ch[j]) return false;
            p = p->ch[j];
        }
        return p->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *p = root;
        for (int i = 0; i < prefix.size(); i++) {
            int j = prefix[i] - 'a';
            if (!p->ch[j]) return false;
            p = p->ch[j];
        }
        return true;
    }
private:
    TrieNode *root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
```

[212. Word Search II](https://leetcode.com/problems/word-search-ii/#/description)
```
Given a 2D board and a list of words from the dictionary, find all words in the board.
Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
For example,
Given words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.
```

```c++
class TrieNode {
public:
    TrieNode *ch[26];
    string key;
    
    TrieNode() : key("") {
        for (int i = 0; i < 26; i++) ch[i] = NULL;
    }
};

class Trie {
public:
    TrieNode *root;
    
    Trie() { root = new TrieNode(); }
    
    void insert(string word) {
        TrieNode *p = root;
        for (char c : word) {
            if (!p->ch[c-'a']) p->ch[c-'a'] = new TrieNode();
            p = p->ch[c-'a'];
        }
        p->key = word;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        if (board.empty() || board[0].empty()) return res;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        Trie T;
        for (string word : words) T.insert(word);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!T.root->ch[board[i][j] - 'a']) continue;
                dfs(board, i, j, T.root->ch[board[i][j] - 'a'], visited, res);
            }
        }
        return res;
    }
    
    void dfs(vector<vector<char>> &board, int x, int y, TrieNode *curNode, vector<vector<bool>> &visited, vector<string> &res) {
        if (!curNode->key.empty()) {
            res.push_back(curNode->key);
            curNode->key.clear(); // to avoid duplicate solutions
        }
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!inBound(board, nx, ny) || !curNode->ch[board[nx][ny]-'a'] || visited[nx][ny]) continue;
            dfs(board, nx, ny, curNode->ch[board[nx][ny]-'a'], visited, res);
                
        }
        visited[x][y] = false;
    }
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<char>> &board, int x, int y) {
        return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
    }
};
```

[211. Add and Search Word - Data structure design](https://leetcode.com/problems/add-and-search-word-data-structure-design/#/description)
```
Design a data structure that supports the following two operations:
void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.
For example:
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
```

```c++
class TrieNode {
public:
    TrieNode *ch[26];
    string key;
    
    TrieNode(): key("") {
        for (int i = 0; i < 26; i++) ch[i] = NULL;
    }
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *p = root;
        for (char c : word) {
            if (!p->ch[c-'a']) p->ch[c-'a'] = new TrieNode();
            p = p->ch[c-'a'];
        }
        p->key = word;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchDFS(word, 0, root);
    }
private:
    TrieNode *root;
    
    bool searchDFS(string word, int matched, TrieNode *curNode) {
        if (matched == word.size()) return !curNode->key.empty();
        if (word[matched] != '.') {
            return curNode->ch[word[matched]-'a'] && searchDFS(word, matched+1, curNode->ch[word[matched]-'a']);
        } else {
            for (int i = 0; i < 26; i++) {
                if (!curNode->ch[i]) continue;
                if (searchDFS(word, matched+1, curNode->ch[i])) return true;
            }
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
```

## Segment Tree

## Kd-Tree

## Skip Linked List



