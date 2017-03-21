/*
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.
*/

// Time: O(mn), Space: O(mn).
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0)); // dp[i][j] := # unique paths passing THROUGH obstacleGrid[i][j]
        // caution: need to initial the first row and first column
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[i][0] == 0) dp[i][0] = 1;
            else break;
        }
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[0][j] == 0) dp[0][j] = 1;
            else break;
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) continue;
                if (obstacleGrid[i-1][j] == 0) dp[i][j] += dp[i-1][j];
                if (obstacleGrid[i][j-1] == 0) dp[i][j] += dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
};

/*
Remark: Whenever we have a DP problem of the type dp[i][j] = function(dp[i-1][j], dp[i][j-1]), we can use the space optimization to use only O(min(m, n)) space.

Time: O(mn), Space: O(min(m, n)).
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty() || obstacleGrid[0][0]) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<int> dp(n);
        dp[0] = 1;
        for (vector<int> row : obstacleGrid) {
            for (int j = 0; j < n; j++) {
                if (row[j] == 1) dp[j] = 0;
                else if (j > 0) dp[j] += dp[j-1];
            }
        }
        return dp[n-1];
    }
};
