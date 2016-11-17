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
        
        // flip the matrix left to right
        for (int i = 0; i < n; i++) {
            int left = 0, right = n-1;
            while (left < right) {
                swap(matrix[i][left], matrix[i][right]);
                left++;
                right--;
            }
        }
        
        // flip the matrix with respect to the bottom left - top right diagnoal
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n-i; j++) {
                swap(matrix[i][j], matrix[n-j-1][n-i-1]);
            }
        }
    }
};
