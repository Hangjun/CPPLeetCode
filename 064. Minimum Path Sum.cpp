/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

// Non-optimized DP. Time: O(mn), Space: O(mn).
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int> (n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++) dp[i][0] = dp[i-1][0] + grid[i][0]; // first column
        for (int j = 1; j < n; j++) dp[0][j] = dp[0][j-1] + grid[0][j]; // first row
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        
        return dp[m-1][n-1];
    }
};

// Space optimized using Roll Arrays. Time: O(mn), Space: O(min(m, n)). Two Rows.
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(2, vector<int> (n, 0));
        dp[0][0] = grid[0][0];
        for (int j = 1; j < n; j++) dp[0][j] = dp[0][j-1] + grid[0][j]; // first row
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) dp[i%2][j] = dp[(i-1)%2][j] + grid[i][j];
                else dp[i%2][j] = min(dp[(i-1)%2][j], dp[i%2][j-1]) + grid[i][j];
            }
        }
        
        return dp[(m-1)%2][n-1];
    }
};

// DP: space optimized. Time: O(mn), Space: O(min(m, n)). One Row.
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, grid[0][0]);
        for (int j = 1; j < n; j++) dp[j] = dp[j-1] + grid[0][j];
        
        for (int i = 1; i < m; i++) {
            dp[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }
        
        return dp[n-1];
    }
};
