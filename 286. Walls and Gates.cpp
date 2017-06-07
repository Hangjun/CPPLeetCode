/*
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
*/

/*
Analysis: The first idea is we BFS search for the nearest gate from every empty room. We need to keep a distance variable to record the shortest distances found. However, this is not the optimal solution as it takes O(m^2n^2) time since for each point in the m*n size grid, the gate could be at most m*n steps away.

Space complexity : O(mn). The space complexity depends on the queue's size. Since we won't insert points that have been visited before into the queue, we insert at most m * n points into the queue.
*/

/*
只有求路径最短的时候，用BFS。其余多数时候用DFS，比如求路径最长，其他指标最大或者最小。此题显然用BFS。
点分为4种：始点、终点、不始不终、又始又终。
始点对其他点施加影响，但自身不受其他点影响。
终点自身受其他点影响，但不对其他点施加影响。
第三类点，既不施加影响，又不接受影响。可以忽略。
第四类点，又施加影响，又接受影响。
如果只求1点，就从该点开始搜索。如果求全局，就要从所有始点和第四类点开始搜索。
此题中，0显然为始点，无穷大显然为终点，-1为第三类点。没有第四类点。所以此题必然是从每个0启动一轮搜索。
例子：
只能用bfs：leetcode 286 / 从某指定点到另一指定点图上最短距离
只能用dfs：poj 1088
只需要从一点搜索：从某指定点到另一指定点图上最短距离
必须从所有点搜索：leetcode 286 / poj 1088
*/

// BFS solution. Time: O(m^2n^2), Space: O(mn).
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        int m = rooms.size(), n = rooms[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) bfsUpdate(rooms, i, j);
            }
        }
    }
    
private:
    void bfsUpdate(vector<vector<int>> &rooms, int i, int j) {
        int m = rooms.size(), n = rooms[0].size();
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (!inBound(rooms, nx, ny) || rooms[nx][ny] == -1) continue;
                if (rooms[x][y] + 1 < rooms[nx][ny]) {
                    rooms[nx][ny] = rooms[x][y] + 1;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }
    
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &rooms, int x, int y) {
        return (x >= 0 && x < rooms.size() && y >= 0 && y < rooms[0].size());
    }
};

/*
The above naive BFS solution is still O(m^2n^2) in the worst case. An improvement is to perform the BFS update for all gates at the same time.
*/

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        int m = rooms.size(), n = rooms[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) q.push(make_pair(i, j));
            }
        }
        
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                /*
                If you reached it quicker via some other Gate it's value would have already been set (no longer INF) 
                and thus your path is longer, so ignore it.
                This is equivalent to a visited mechnism, making the algorithm runs in time O(mn).
                */
                if (!inBound(rooms, nx, ny) || rooms[nx][ny] != INT_MAX) continue;
                rooms[nx][ny] = rooms[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &rooms, int x, int y) {
        return (x >= 0 && x < rooms.size() && y >= 0 && y < rooms[0].size());
    }
};


/*
Remark: 
If you are having difficulty to derive the time complexity, start simple.

Let us start with the case with only one gate. The breadth-first search takes at most m * n steps to reach all rooms, therefore the time complexity is O(mn). But what if you are doing breadth-first search from k gates?

Once we set a room's distance, we are basically marking it as visited, which means each room is visited at most once. Therefore, the time complexity does not depend on the number of gates and is O(mn).

We can actually also use DFS to solve this problem. The key is to pass on the "rooms[x][y] + 1 < rooms[nx][ny]" information during each DFS recursion call:
*/

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        int m = rooms.size(), n = rooms[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) dfsUpdate(rooms, i, j);
            }
        }
    }
    
private:
    void dfsUpdate(vector<vector<int>> &rooms, int x, int y) {
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!inBound(rooms, nx, ny) || rooms[nx][ny] == -1 || rooms[x][y] + 1 >= rooms[nx][ny]) continue;
            rooms[nx][ny] = rooms[x][y] + 1;
            dfsUpdate(rooms, nx, ny);
        }
    }
    
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &rooms, int x, int y) {
        return (x >= 0 && x < rooms.size() && y >= 0 && y < rooms[0].size());
    }
};
