/*
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int n = matrix.size();
        
        // rotate matrix left to right vertically
        for (int i = 0; i < n; i++) {
            int left = 0, right = n-1;
            while (left < right) swap(matrix[i][left++], matrix[i][right--]);
        }
        
        // rotate matrix w.r.t. bottom-right diagonal. Caution: do not over rotate!
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n-i; j++) { // i+j < n
                swap(matrix[i][j], matrix[n-j-1][n-i-1]); // caution: not flip with matrix[n-i-1][n-j-1]!
            }
        }
    }
};
