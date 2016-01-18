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

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        // serialize grid
        vector<int> parent(m*n);
        // initialize parent to be itself
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                parent[i * n + j] = i * n + j;
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
                        int nx = dx[k];
                        int ny = dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            unite(parent, t, nt);
                        }
                    }
                }
            }
        }
        // count the number of distinct parents
        unordered_set<int> res;
        for (int i = 0; i < parent.size(); i++) {
            res.insert(parent[i]);
        }
        return res.size();
    }
private:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
                    
    int find(vector<int> &parent, int t) {
        if (t != parent[t]) {
            parent[t] = find(parent, parent[t]);
        }
        return parent[t];
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

/* Analysis:
When we count the number of islands on lines 63 - 68, we included water components as well. Need to exclude those.
*/

/* Submission #2: Failed after changing the counting logic to if (parent[i] != 0) res.insert(parent[i]);
Submission Result: Wrong Answer
Input: ["1"]
Output: 0
Expected: 1 
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        // serialize grid
        vector<int> parent(m*n);
        // initialize parent to be itself
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                parent[i * n + j] = i * n + j;
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
                        int nx = dx[k];
                        int ny = dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            unite(parent, t, nt);
                        }
                    }
                }
            }
        }
        // count the number of distinct parents
        unordered_set<int> res;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != 0) {
                res.insert(parent[i]);
            }
        }
        return res.size();
    }
private:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
                    
    int find(vector<int> &parent, int t) {
        if (t != parent[t]) {
            parent[t] = find(parent, parent[t]);
        }
        return parent[t];
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

/* Analysis:
We often initialize parents to be the node index itself. Howver in this case, we need also to distinguish island node ('1') and water node 
('0'). Therefore initializing parents to be some other sentinal value, e.g. -1, might be more conveinient.
*/

/* Submission #3: Failed
Submission Result: Wrong Answer
Input: ["1011011"]
Output: 5
Expected: 3 
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        // serialize grid: initialize parent to be -1
        vector<int> parent(m*n, -1);
        // scan grid: once '1' is found, merge it with neighboring nodes
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    int t = i * n + j;
                    // update parent node once
                    int pt = find(parent, t);
                    // search neighboring island nodes
                    for (int k = 1; k <= 4; k++) {
                        int nx = dx[k];
                        int ny = dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            unite(parent, t, nt);
                        }
                    }
                }
            }
        }
        // count the number of distinct parents
        unordered_set<int> res;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                res.insert(parent[i]);
            }
        }
        return res.size();
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

/* Analysis:
We missed one bug: on lines 202, 203, the neighboring node's coordinates should be nx = i + dx[k], and ny = j + dy[k].
*/

/* Submission #4: Failed
Submission Result: Wrong Answer
Input: ["10111","10101","11101"]
Output: 2
Expected: 1 
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        // serialize grid: initialize parent to be -1
        vector<int> parent(m*n, -1);
        // scan grid: once '1' is found, merge it with neighboring nodes
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    int t = i * n + j;
                    // update parent node once
                    int pt = find(parent, t);
                    // search neighboring island nodes
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            unite(parent, t, nt);
                        }
                    }
                }
            }
        }
        // count the number of distinct parents
        unordered_set<int> res;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                res.insert(parent[i]);
            }
        }
        return res.size();
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

/* Analysis: 
We are missing one important point here: one key point of union-find is that we only merge the ultimate parents. Therefore, after the union-find
routine finishes, some child nodes might not be flatterned to point to the ultimate parents. Even though we perform path comparession (
i.e. flatterning) everytime we call find(), when merging the last two big components, it is conceivable that only the big bothers pointers
are changed, and within each of the two components, (some of) the child nodes are flatterned since to find the big brothers, we executed a find().
In problem 323 we got away with this since we kept a counter variable that counts the number of merged components. Here we didn't have such a
counter. Changing res.insert(parent[i]); on line 297 to res.insert(find(parent,i)); should fix this:
*/

// Submission #5: Accepted

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        // serialize grid: initialize parent to be -1
        vector<int> parent(m*n, -1);
        // scan grid: once '1' is found, merge it with neighboring nodes
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    int t = i * n + j;
                    // update parent node once
                    int pt = find(parent, t);
                    // search neighboring island nodes
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            unite(parent, t, nt);
                        }
                    }
                }
            }
        }
        // count the number of distinct parents
        unordered_set<int> res;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                res.insert(find(parent, i));
            }
        }
        return res.size();
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

/* 
To verify the commends we made about the counter, here is another implementation that serves as a santity check:
*/

// Submission #6: Accepted.

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
                    for (int k = 0; k < 4; k++) {
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

/* Analysis:
Lnes 453 to 454 seems less elegant: if (pt != pnt), we still call find() twice to get pt and pnt again in the unite routine. We can effectively
remove this check inside unite(). In fact, we can remove the entire unite routine:
*/

// Submission #7: Accepted.

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
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if(inbound(grid, nx, ny) && grid[nx][ny] == '1') {
                            int nt = nx * n + ny;
                            int pnt = find(parent, nt);
                            if (pt != pnt) {
                                parent[pt] = min(pt, pnt);
                                parent[pnt] = min(pt, pnt);
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
    
    bool inbound(vector<vector<char>> &grid, int x, int y) {
        return (x >=0 && x < grid.size() && y >= 0 && y < grid[0].size());
    }
};
