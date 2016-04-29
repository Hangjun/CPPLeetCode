/*
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

click to show hint.

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
*/

class TrieNode {
public:
    TrieNode *ch[26];
    string str;
    
    TrieNode() : str(""){
        for (int i = 0; i < 26; i++) ch[i] = NULL;
    }
};

class Trie {
public:
    TrieNode *root;
    
    Trie() { root = new TrieNode(); }
    void insert(string key) {
        TrieNode *p = root;
        for (int i = 0; i < key.size(); i++) {
            int j = key[i] - 'a';
            if (!p->ch[j]) p->ch[j] = new TrieNode();
            p = p->ch[j];
        }
        p->str = key;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        if (words.empty() || board.empty() || board[0].empty()) return res;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        Trie T;
        for (auto &a : words) T.insert(a);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (T.root->ch[board[i][j] - 'a']) {
                    searchDFS(board, T.root->ch[board[i][j] - 'a'], i, j, visited, res);
                }
            }
        }
        return res;
    }
    
    void searchDFS(vector<vector<char>> &board, TrieNode *curNode, int x, int y, vector<vector<bool>> &visited, vector<string> &res) {
        // terminating condition
        if (!curNode->str.empty()) {
            res.push_back(curNode->str);
            curNode->str.clear();
        }
        
        // dfs on neighbors
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (inbound(board, nx, ny) && !visited[nx][ny] && curNode->ch[board[nx][ny] - 'a']) {
                searchDFS(board, curNode->ch[board[nx][ny] - 'a'], nx, ny, visited, res);
            }
        }
        visited[x][y] = false;
    }
    
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inbound(vector<vector<char>> &board, int x, int y) {
        return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
    }
};
