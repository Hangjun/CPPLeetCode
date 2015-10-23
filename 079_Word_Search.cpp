Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // corner case
        if (board.empty() || board[0].empty())  return false;
        if (word.empty())  return true;
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (existDFS(board, i, j, word, 1, visited))
                        return true;
                }
            }
        }
        return false;
    }
    
    bool existDFS(vector<vector<char>> &board, int x, int y, string word, int index, vector<vector<bool>> &visited) {
        // terminate condition
        if (index == word.size()) {
            return true;
        }
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (inBound(board, nx, ny) && board[nx][ny] == word[index] && !visited[nx][ny]) {
                if(existDFS(board, nx, ny, word, index+1, visited))
                    return true;
            }
        }
        visited[x][y] = false;
        return false;
    }
    
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<char>> &board, int x, int y) {
        int m = board.size();
        int n = board[0].size();
        return (x >= 0 && x < m && y >= 0 && y < n);
    }
};

