/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.
*/

/*
Analysis: This is a typical DP problem. We can define the state dp[i][j] to be the minimum costs of painting up to house i, such that the ith house is painted with color j. It is easy to see that the transfer function is:
dp[i][j] = min{dp[i-1][k] | k != j} + costs[i][j].

The straightfoward implementation below takes:
Time O(n), Space O(n), where n = number of houses.
*/
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int res = INT_MAX;
        int m = costs.size(), n = costs[0].size();
        vector<vector<int>> dp(m, vector<int>(n)); // dp[i][j] = min cost of painting up to house i with color j
        dp[0] = costs[0];
        
        for (int i = 1; i < m; i++) {
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0];
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1];
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2];
        }
        
        for (int j = 0; j < n; j++) res = min(res, dp[m-1][j]);
        return res;
    }
};

/* 
Analysis: We can improve the space complexity to O(1) using the method of rolling array, as only two rows (dp[i-1][] and dp[i][]) are needed.
*/
// Time: O(n), Space: O(1). n = number of houses.
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int res = INT_MAX;
        int m = costs.size(), n = costs[0].size();
        vector<vector<int>> dp(2, vector<int>(n)); // dp[i][j] = min cost of painting up to house i with color j
        dp[0] = costs[0];
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i%2][j] = min(dp[(i-1)%2][(j+1)%n], dp[(i-1)%2][(j+2)%n]) + costs[i][j];
            }
        }
        
        for (int j = 0; j < n; j++) res = min(res, dp[(m-1)%2][j]);
        return res;
    }
};
