/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
*/

/*
Analysis: We want to expand the max square search from some starting point. Canonically we start from the top left corner (0, 0). Thus a state can be defined as dp[i][j] := max size of the square ending at (i, j), i.e. (i, j) is the bottom right point. We use size, the square root of the area, for simplicity.

Time: O(mn), Space: O(mn).
*/
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0)); // dp[i][j] = max size of square ending at (i, j)
        int maxSize = 0;
        for (int i = 0; i < m; i++) {
            dp[i][0] = matrix[i][0] == '1';
            maxSize = max(maxSize, dp[i][0]);
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j] == '1';
            maxSize = max(maxSize, dp[0][j]);
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '0') continue;
                dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                maxSize = max(maxSize, dp[i][j]);
            }
        }
        
        return maxSize * maxSize;
    }
};

/*
Analysis: It is again a DP problem where the state transition of dp[i][j] only depends on dp[i-1][j], dp[i][j-1] and dp[i-1][j-1]. We can always optimize the space complexity by using only two rows, that is the rolling array trick. We can also use two columns, but we can fix a style to minimize the cost of memorization.

Time: O(mn), Space: O(min(m, n)).
*/
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(2, vector<int>(n, 0)); // dp[i][j] = max size of square ending at (i, j)
        int maxSize = 0;
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j] == '1';
            maxSize = max(maxSize, dp[0][j]);
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    dp[i%2][j] = matrix[i][j] == '1';
                } else if (matrix[i][j] == '1') {
                    dp[i%2][j] = min(min(dp[(i-1)%2][j], dp[i%2][j-1]), dp[(i-1)%2][j-1]) + 1;
                } else {
                    dp[i%2][j] = 0; // necessary to overwrite previously written value here
                }

                maxSize = max(maxSize, dp[i%2][j]);
            }
        }
        
        return maxSize * maxSize;
    }
};

/*
We can further optimize the space complexity to using only one row/column.
*/
