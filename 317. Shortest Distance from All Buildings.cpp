/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
*/

// TLE solution. Time: O(m^2 n^2), Space: O(mn).
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return -1;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, 0)); // shortest distance from all buildings to a empty space
        vector<vector<int>> reachableBuildings(m, vector<int>(n, 0)); // total number of buildings reachable from a space
        int buildingCount = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 1) continue;
                ++buildingCount;
                // (i, j) is a building. BFS from it and get all empty spaces reachable
                queue<pair<int, int>> q;
                int level = 1;
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                visited[i][j] = true;
                q.push(make_pair(i, j));
                while (!q.empty()) {
                    int sz = q.size(); // avoid using two queues: this is a level order enforcer
                    for (int k = 0; k < sz; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (!inBound(grid, nx, ny) || visited[nx][ny] || grid[nx][ny] != 0) continue;
                        // (nx, ny) is an empty space
                        dist[nx][ny] += level;
                        reachableBuildings[nx][ny]++;
                        visited[nx][ny] = true;
                        q.push(make_pair(nx, ny));
                    }
                    level++;
                }
            }
        }
        
        int res = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 0 || reachableBuildings[i][j] != buildingCount) continue;
                res = min(res, dist[i][j]);
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
    
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &grid, int x, int y) {
        return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size());
    }
};
