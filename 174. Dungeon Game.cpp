/*
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)	-3	3
-5	-10	1
10	30	-5 (P)

Notes:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
*/

/*
Analysis: It does not take too much time for one to realizee that we need to compute the minimum health required backwards - from the princess block on the bottom-right.

Time: O(mn), Space: O(mn)
*/

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if (dungeon.empty() || dungeon[0].empty()) return 0;
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m, vector<int>(n)); // dp[i][j] = minimum health required to enter dungeon[i][j]
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = dungeon[i][j];
            }
        }
        
        dp[m-1][n-1] = max(-dungeon[m-1][n-1], 0);
        // initialize last column
        // dp[i+1][n-1] - dp[i][n-1] is the cost of entrying [i+1][n-1] from [i][n-1]
        for (int i = m-2; i >= 0; i--) dp[i][n-1] = max(dp[i+1][n-1] - dp[i][n-1], 0); 
        // initial last row
        for (int j = n-2; j >= 0; j--) dp[m-1][j] = max(dp[m-1][j+1] - dp[m-1][j], 0);
        
        for (int i = m-2; i >= 0; i--) {
            for (int j = n-2; j >= 0; j--) {
                dp[i][j] = max(min(dp[i+1][j], dp[i][j+1]) - dp[i][j], 0);
            }
        }
        return dp[0][0]+1;
    }
};
