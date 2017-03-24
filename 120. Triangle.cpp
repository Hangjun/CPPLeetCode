/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/

/*
Time: O(n^2), Space: O(n).
*/
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(triangle.back()); // dp[i] = minimum path sum reaching node i
        for (int l = n-2; l >= 0; l--) {
            for (int i = 0; i < triangle[l].size(); i++) {
                dp[i] = min(dp[i], dp[i+1]) + triangle[l][i];
            }
        }
        return dp[0];
    }
};
