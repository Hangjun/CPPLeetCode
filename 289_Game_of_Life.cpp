/*
According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

    Any live cell with fewer than two live neighbors dies, as if caused by under-population.
    Any live cell with two or three live neighbors lives on to the next generation.
    Any live cell with more than three live neighbors dies, as if by over-population..
    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Write a function to compute the next state (after one update) of the board given its current state.

Follow up:

    Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
    In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
*/

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        // corner case
        if (board.empty() || board[0].empty()) return;
        // we using decoding to represent temp state:
        // 0: currentl state = 0, next state = 0;
        // 1: current state = 1, next state = 1;
        // 2: current state = 1, next state = 0;
        // 3: current state = 0, next state = 1;
        // after marking each point, we decode the states vid mod 2
        int m = board.size();
        int n = board[0].size();
        // process the board and mark the states
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int lives = 0;
                if (i > 0) { // top
                    lives += board[i-1][j] == 1 || board[i-1][j] == 2 ? 1 : 0;
                }
                if (j > 0) { // left
                    lives += board[i][j-1] == 1 || board[i][j-1] == 2 ? 1 : 0;
                }
                if (i < m-1) { // down
                    lives += board[i+1][j] == 1 || board[i+1][j] == 2 ? 1 : 0;
                }
                if (j < n-1) { // right
                    lives += board[i][j+1] == 1 || board[i][j+1] == 2 ? 1 : 0;
                }
                if (i > 0 && j > 0) { // top left
                    lives += board[i-1][j-1] == 1 || board[i-1][j-1] == 2 ? 1 : 0;
                }
                if (i > 0 && j < n-1) { // top right
                    lives += board[i-1][j+1] == 1 || board[i-1][j+1] == 2 ? 1 : 0;
                }
                if (i < m-1 && j > 0) { // down left
                    lives += board[i+1][j-1] == 1 || board[i+1][j-1] == 2 ? 1 : 0;
                }
                if (i < m-1 && j < n-1) { // down right
                    lives += board[i+1][j+1] == 1 || board[i+1][j+1] == 2 ? 1 : 0;
                }
                // update state for cell(i, j)
                if (board[i][j] == 1 && (lives < 2 || lives > 3)) {
                   board[i][j] = 2;
                }
                if (board[i][j] == 0 && lives == 3) {
                    board[i][j] = 3;
                }
            }
        }
        // decode
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = board[i][j] % 2;
            }
        }
    }
};
