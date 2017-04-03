/*
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
*/

/*
Analysis: This is obviously a DP problem. The subproblems are also easy to construct: if we can know the minimum number of coins need to sum up to a value less than the target amount, then we can compute the minimum number of coins need to sum up to target amount. This actually also defines the states as well as the state transition functions.

This problem is essentially the same as problem 279. Perfect Squares (https://leetcode.com/problems/perfect-squares/#/description). Whenever it comes to finding the minimum number of summands.

Time: O(n*amount), Space: O(amount). We cannot optimize the space complexity as the state transition function is not continuous.
*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (coins.empty() || amount < 0) return -1;
        int n = coins.size();
        vector<int> dp(amount+1, amount+1); // dp[i] = min # of coins needed to sum up to value i
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < n; j++) {
                if (i >= coins[j]) dp[i] = min(dp[i], dp[i-coins[j]]+1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

/*
Follow up: What if we want to output the total number of different ways to sum up to the target amount? It is still a DP problem, and the subproblem becomes dp[i][j] := the number of ways to sum up to value i with the coins[0:j].\

When counting the number of ways to arrange the summands to sum up to a target value, the state can be divided into two cases: including the current value or not - just like the 0/1 Knapsack Problem.

Problem Link: http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/.
Github Link: 
*/
int count(vector<int> &coins, int amount) {
    if (coins.empty() || amount < 0) return 0;
    int n = coins.size();
    vector<vector<int>> dp(amount+1, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[0][i] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            // count the solution including s[j]
            int x = i >= s[j] ? dp[i-s[j]][j] : 0;
            
            // count the solution excluding s[j]
            int y = j >= 1 ? dp[i][j-1] : 0;
            
            dp[i][j]= x+ y;
        }
    }
    
    return dp[amount][n-1];
}
