/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
Example 1:
11110
11010
11000
00000
Answer: 1
Example 2:
11000
11000
00100
00011
Answer: 3
*/

/* Submission #1: Failed
Submission Result: Wrong Answer
Input: ["0"]
Output: 1
Expected: 0 
*/

// Union-Find solution

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        // serialize grid: initialize parent to be -1
        vector<int> parent(m*n, -1);
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    count++;
                }
            }
        }
        // scan grid: once '1' is found, merge it with neighboring nodes
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    int t = i * n + j;
                    // update parent node once
                    int pt = find(parent, t);
                    // search neighboring island nodes
                    for (int k = 1; k <= 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            int pnt = find(parent, nt);
                            if (pt != pnt) {
                                unite(parent, t, nt);
                                count--;
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
private:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
                    
    int find(vector<int> &parent, int t) {
        if (parent[t] == -1) {
            parent[t] = t;
            return parent[t];
        }
        int pt = t;
        while (pt != parent[pt]) pt = parent[pt];
        int f = t;
        while (f != pt) {
            int tmp = parent[f];
            parent[f] = pt;
            f = tmp;
        }
        return pt;
    }
    
    void unite(vector<int> &parent, int t, int nt) {
        int pt = find(parent, t);
        int pnt = find(parent, nt);
        if (pt != pnt) {
            parent[pt] = min(pt, pnt);
            parent[pnt] = min(pt, pnt);
        }
    }
    
    bool inbound(vector<vector<char>> &grid, int x, int y) {
        return (x >=0 && x < grid.size() && y >= 0 && y < grid[0].size());
    }
};
