/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size();
        int n = matrix[0].size();
    
        // avoid searching out of bound
        if (target < matrix[0][0] || target > matrix[m-1][n-1]) return false;
        
        // start binary search with the left corner
        int left = m-1; 
        int right = 0;
        
        while (left >= 0 && right < n) {
            if (matrix[left][right] == target) return true;
            else if (matrix[left][right] < target) right++;
            else left--;
        }
        
        return false;
    }
};
