/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/*
Time: O(n), Space: O(n). 2 Passes.
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        int localMax = 0;
        vector<int> dp(n, 0); // dp[i] = max profit made at index i
        int curLow = prices[0];
        for (int i = 1; i < n; i++) {
            int curProfit = prices[i] - curLow;
            localMax = max(localMax, curProfit);
            dp[i] = localMax;
            curLow = min(curLow, prices[i]);
        }
        
        int globalMax = dp[n-1];
        localMax = 0;
        int curHigh = prices[n-1];
        for (int i = n-2; i >= 0; i--) {
            int curProfit = curHigh - prices[i];
            localMax = max(localMax, curProfit);
            globalMax = max(globalMax, dp[i] + localMax);
            curHigh = max(curHigh, prices[i]);
        }
        
        return globalMax;
    }
};
