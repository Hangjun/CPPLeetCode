/*
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]

Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]

Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/

/* Analysis:
There are several bugs in the above implementation:
1. We don't need to use the visited array. Checking whether dp has been updated is enough to not run into a node again on two different 
DFS traversals. What's unique about this problem is that, once dp[i][j] is calculated for node (i,j), it is globally optimal. 
Caution that this is NOT always the case with DFS. Here we have the optimality guarantee due to the monotonicity property of each DFS.

In fact, we cannot use a visited array to avoid visiting a node twice on the same DFS traversl, or globally, at least not trivially. 
Here DFS traversals actually need to pass information (namely the length of the longest path) upward, thus if a neighboring node was 
previously visited, we would like to fetch its dp value. Using a visited array naively as before, for instance, as 
if (inbound(matrix, nx, ny) && !visited[nx][ny] && matrix[nx][ny] > matrix[x][y])
is not going to let us fetch dp[nx][ny]. 

Moreover, we are actually only worried about visiting the same node twice globally. Since we require traversing monotonically, we won't 
bump into a node twice on the same DFS tour. 

2. Defining dp[i][j] properly is critically logically important. Here dp[i][j] should be defined as the length of the longest increasing 
path EMINATING from (i, j), not ending at (i, j). This way, if we have a neighbor (ni, nj) with matrix[ni][nj] > matrix[i][j], we can 
do a DFS to compute dp[ni][nj] recursively and "trust" this by setting dp[i][j] := max(dp[i][j], 1 + dp[ni][nj]). If 1 + dp[ni][nj] is 
larger, than we would get a longer path by re-routing (i, j) to go through (ni, nj).
This is an application of the optimality property we have discussed. Thus line 70 above should be: 
dp[x][y] = max(dp[x][y], dfs(matrix, nx, ny, dp)).

3. Initializing dp to be zero is imporant, since any positive value is plausible but not zero. 
*/

// Version #1
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        // dp[i][j] = length of longest increasing path that STARTS from (i,j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxLen = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // dfs returns maximum length of the increasing path that reaches (i, j)
                int curLen = dfs(matrix, i, j, dp);
                maxLen = max(maxLen, curLen);
            }
        }
        return maxLen;
    }
    
private:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    
    int dfs(vector<vector<int>> &matrix, int x, int y, vector<vector<int>> &dp) {
        if (dp[x][y] != 0) return dp[x][y];

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (inbound(matrix, nx, ny) && matrix[nx][ny] > matrix[x][y]) {
                // route (x, y) to go through (nx, ny) to get a longer path
                dp[x][y] = max(dp[x][y], dfs(matrix, nx, ny, dp));
            }
        }
        return ++dp[x][y];
    }
    
    bool inbound(vector<vector<int>> &matrix, int x, int y) {
        return (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size()); 
    }
};


// Version #2
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        // dp[i][j] = length of longest increasing path that STARTS from (i,j)
        vector<vector<int>> dp(m, vector<int>(n, 1));
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int maxLen = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // dfs returns maximum length of the increasing path that reaches (i, j)
                int curLen = dfs(matrix, i, j, visited, dp);
                maxLen = max(maxLen, curLen);
            }
        }
        return maxLen;
    }
    
private:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    
    int dfs(vector<vector<int>> &matrix, int x, int y, vector<vector<bool>> &visited, vector<vector<int>> &dp) {
        //if (dp[x][y] != 0) return dp[x][y];
        if (visited[x][y]) return dp[x][y];
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (inbound(matrix, nx, ny) && matrix[nx][ny] > matrix[x][y]) {
                // route (x, y) to go through (nx, ny) to get a longer path
                dp[x][y] = max(dp[x][y], 1 + dfs(matrix, nx, ny, visited, dp));
            }
        }
        visited[x][y] = true;
        return dp[x][y];
    }
    
    bool inbound(vector<vector<int>> &matrix, int x, int y) {
        return (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size()); 
    }
};
