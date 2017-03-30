/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
*/

/*
Analysis: The first idea is to build up the result incrementally. Then the idea naturally following that is to use DP. The state transition function is the slightly tricky part. Similar to Problem 338. Counting Bits, the transition is based on the difference of the current value and the previously computed value.

Time: O(n^2), Space: O(n).
*/
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = i; // sum of i 1's
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
};

/*
Remark: There is another solution that tranforms this problem to finding the smallest path via BFS in a graph. The graph nodes are 0, 1, ..., n, and there is another edge from i to j if and only if j = i + (some perfect square). We won't include this solution here.
*/
