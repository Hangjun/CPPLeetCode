/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.
*/

/*
Analysis: An intuitive algorithm is to do binary search twice: once to locate the row, and another time to search in that row. We can actually do binary search only once. The only reference is the left bottom entry. This is called the Stepwise Linear Search.

Time: O(max{m, n}), Space: O(1). 1 Binary Search.
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        // without this check the algorithm will run out of bound
        if (target < matrix[0][0] || target > matrix[m-1][n-1]) return false; 
        int row = m-1, col = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                row--;
            } else {
                col++;
            }
        }
        return false;
    }
};
