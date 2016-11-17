/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) return 1;
        
        // dp[i] = #distinct ways to get to the first i stairs, i.e. stiares 0 through i-1
        vector<int>dp(n+1, 0);
        
        // initialization
        dp[0] = 1;
        dp[1] = 1;
        
        // transfer function
        for (int i = 2; i < n+1; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
};
