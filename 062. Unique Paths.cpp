/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Note: m and n will be at most 100.
*/

/*
Time: O(mn), Space: O(mn).
*/
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

/*
Analysis: For every DP problem, we ask ourselves whether we can improve on the space complexity. For this problem, for each dp[i][j], all we needed was the value before it at the same ith row, and the value above at the previous (i-1)th row. Therefore we only need to keep track of two rows.

Time: O(mn), Space: O(min(m, n)). 2 Arrays
*/
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m < n) return uniquePaths(n, m);
        vector<int> prevRow(n, 1);
        vector<int> curRow(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                curRow[j] = curRow[j-1] + prevRow[j];
            }
            swap(prevRow, curRow);
        }
        return prevRow[n-1];
    }
};

/*
Instead of doing the update and then swap, we can actually directly overwrite the current rows' value since prevRow is simply curRow before its update. This way we only need one array.

Time: O(mn), Space: O(min(m, n)). 1 Array.
*/
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m < n) return uniquePaths(n, m);
        vector<int> curRow(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++)
                curRow[j] += curRow[j-1];
        }
        return curRow[n-1];
    }
};
