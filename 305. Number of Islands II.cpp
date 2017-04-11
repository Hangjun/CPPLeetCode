/*
A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
We return the result as an array: [1, 1, 2, 3]

Challenge:

Can you do it in time complexity O(k log mn), where k is the length of the positions?
*/

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> res;
        if (positions.empty()) return res;
        vector<vector<int>> grid(m, vector<int>(n, 0));
        vector<int> parent(m*n, -1);
        for (auto p : positions) {
            int x = p.first, y = p.second;
            grid[x][y] = 1;
            int t = x * n + y;
            int pt = find(parent, t);
            if (res.empty()) { // first point
                res.push_back(1);
                continue;
            }
            // find connected components of (x,y)'s neighbors
            unordered_set<int> pNode;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (!inBound(grid, nx, ny) || grid[nx][ny] != 1) continue;
                int nt = nx * n + ny;
                int pnt = find(parent, nt);
                pNode.insert(pnt);
            }
            res.push_back(res.back()-(pNode.size()-1));
            
            // union (x,y) with neighbors
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (!inBound(grid, nx, ny) || grid[nx][ny] != 1) continue;
                int nt = nx * n + ny;
                int pnt = find(parent, nt);
                if (pt != pnt) myUnion(parent, t, nt);
            }
        }
        
        return res;
    }
    
private:
    
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
    
    void myUnion(vector<int> &parent, int t, int nt) {
        int pt = find(parent, t);
        int pnt = find(parent, nt);
        if (pt != pnt) { // union the big brothers
            parent[pt] = min(pt, pnt);
            parent[pnt] = min(pt, pnt);
        }
    }
    
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    
    bool inBound(vector<vector<int>> &grid, int x, int y) {
        return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size());
    }
};
