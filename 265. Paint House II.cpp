/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Follow up:
Could you solve it in O(nk) runtime?
*/

// Time: O(nk), Space: O(k). n = number of houses, k = number of colors
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int res = INT_MAX;
        int m = costs.size(), n = costs[0].size();
        vector<vector<int>> dp(2, vector<int>(n)); // dp[i][j] = min cost of painting up to house i with color j
        dp[0] = costs[0];
        
        for (int i = 1; i < m; i++) {
            pair<int, int> p = findSmallests(dp[(i-1)%2]);
            for (int j = 0; j < n; j++) {
                dp[i%2][j] = ( j != p.first ? dp[(i-1)%2][p.first] : dp[(i-1)%2][p.second]) + costs[i][j];
            }
        }
        
        for (int j = 0; j < n; j++) res = min(res, dp[(m-1)%2][j]);
        return res;
    }
private:
    pair<int, int> findSmallests(vector<int> &nums) {
        int p1 = 0, p2 = -1; // p1 = smallest, p2 = second smallest
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[p1]) {
                p2 = p1;
                p1 = i;
            } else if (p2 == -1 || (p2 != -1 && nums[i] < nums[p2])) {
                p2 = i;
            }
        }
        return make_pair(p1, p2);
    }
};
