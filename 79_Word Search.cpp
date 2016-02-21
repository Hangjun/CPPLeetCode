/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {\
        if (word.empty()) return true;
        if (board.empty() || board[0].empty()) return false;
        
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) { // restart DFS search eminating from board[i][j]
                    if (existDFS(board, i, j, word, 1, visited)) {return true;}
                }
            }
        }
        
        return false;
    }
    
    bool existDFS(vector<vector<char>> &board, int x, int y, const string target, int matchedSoFar, vector<vector<bool>> &visited) {
        // check terminating conditions
        if (matchedSoFar == target.size()) { // have matched all characters of target
            return true;
        }
        
        visited[x][y] = true;
        
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (inbound(board, nx, ny) && !visited[nx][ny] && board[nx][ny] == target[matchedSoFar]) {
                if (existDFS(board, nx, ny, target, matchedSoFar+1, visited)) {return true;}
            }
        }
        
        visited[x][y] = false;
        return false;
    }
    
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inbound(vector<vector<char>> &board, int x, int y) {
        return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
    }
    
};


/* Comment:
In the main for-loops, on line 32, we do not need to check whether [i][j] is visited since we are already re-initiating a search starting 
from board[i][j].
*/
