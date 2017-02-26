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
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
};

/* 
Remark: if we generalize this problem so that we can walk up to k stairs at once, we can solve it in a similar way (this is LinkedIn interview question)
*/
class Solution {
public:
    int climbStairs(int n, int k) {
        if (n <= 1) return n;
        if (k < 1) return 0;
        
        // dp[i] = #distinct ways to get to the first i stairs, i.e. stiares 0 through i-1
        vector<int>dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        
        // transfer function
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= k && j <= n; j++) {
                dp[i] += dp[n-j];
            }
        }
        
        return dp[n];
    }
};
