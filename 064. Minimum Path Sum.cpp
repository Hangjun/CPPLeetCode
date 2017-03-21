/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

// DP: space optimized. Time: O(mn), Space: O(min(m, n)).
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
