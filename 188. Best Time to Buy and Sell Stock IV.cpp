/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/*
Analysis: We use local-global DP algorithm. Usually for this type of DP problem, local stores the current state that ends at 
the current index, global stores the optimal state that's up to and including the current index.

Time: O(nk), Space: O(nk).
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) return 0;
        if (k >= prices.size()) return maxProfit(prices); // can make transaction every day - reduces to part II of this series
        int n = prices.size();
        // local[i][j] = max profit with at most j transactions and the ith day a sell
        vector<vector<int>> local(n, vector<int>(k+1, 0));
        // global[i][j] = max profit with at most j transactions from 0th day to ith day
        vector<vector<int>> global(n, vector<int>(k+1, 0));
        
        for (int i = 1; i < n; i++) {
            int delta = prices[i] - prices[i-1];
            for (int j = 1; j <= k; j++) {
                local[i][j] = max(global[i-1][j-1] + max(delta, 0), local[i-1][j] + delta);
                global[i][j] = max(local[i][j], global[i-1][j]);
            }
        }
        
        return global[n-1][k];
    }
    
    int maxProfit(vector<int> &prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            int delta = prices[i] - prices[i-1];
            if (delta > 0) res += delta;
        }
        
        return res;
    }
};

// Standard rolling array trick brings the space complexity down to O(k).
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) return 0;
        if (k >= prices.size()) return maxProfit(prices); // can make transaction every day - reduces to part II of this series
        int n = prices.size();
        // local[i][j] = max profit with at most j transactions and the ith day a sell
        vector<vector<int>> local(2, vector<int>(k+1, 0));
        // global[i][j] = max profit with at most j transactions from 0th day to ith day
        vector<vector<int>> global(2, vector<int>(k+1, 0));
        
        for (int i = 1; i < n; i++) {
            int delta = prices[i] - prices[i-1];
            for (int j = 1; j <= k; j++) {
                local[i%2][j] = max(global[(i-1)%2][j-1] + max(delta, 0), local[(i-1)%2][j] + delta);
                global[i%2][j] = max(local[i%2][j], global[(i-1)%2][j]);
            }
        }
        
        return global[(n-1)%2][k];
    }
    
    int maxProfit(vector<int> &prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            int delta = prices[i] - prices[i-1];
            if (delta > 0) res += delta;
        }
        
        return res;
    }
};
