/*
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
*/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        return isValidRow(board) && isValidCol(board) && isValidBlock(board);    
    }
    
private:
    bool isValidRow(vector<vector<char>> &board) {
        int count[9];
        for (int i = 0; i < 9; i++) {
            memset(count, 0, 9 * sizeof(int));
            for (int j = 0; j < 9; j++) {
                if (!pass(count, board[i][j])) return false;
            }
        }
        return true;
    }
    
    bool isValidCol(vector<vector<char>> &board) {
        int count[9];
        for (int j = 0; j < 9; j++) {
            memset(count, 0, 9 * sizeof(int));
            for (int i = 0; i < 9; i++) {
                if (!pass(count, board[i][j])) return false;
            }
        }
        return true;
    }
    
    bool isValidBlock(vector<vector<char>> &board) {
        int centers[9][2] = {{1, 1}, {1, 4}, {1, 7}, {4, 1}, {4, 4}, {4, 7}, {7, 1}, {7, 4}, {7, 7}};
        int neighbors[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
        int count[9];
        
        for (int i = 0; i < 9; i++) {
            memset(count, 0, 9*sizeof(int));
            pass(count, board[centers[i][0]][centers[i][1]]);
            for (int j = 0; j < 8; j++) {
                if (!pass(count, board[centers[i][0] + neighbors[j][0]][centers[i][1] + neighbors[j][1]]))
                    return false;
            }
        }
        return true;
    }
    
    bool pass(int *count, char c) {
        if (c == '.') return true;
        return (++count[c - '1'] <= 1);
    }
};
