/*
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.

The above image represents the elevation map [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.


After the rain, water are trapped between the blocks. The total volume of water trapped is 4.
*/

/*
Analysis: We follow the single pass idea that solves part I of this problem: starting from the boundary and work our way inward (via DFS or BFS). Now the question is, which boundary element do we start with? We should start with the minimum height! This for the same reason as the if and else condition in lines 9-15 above in Trapping Rain Water: if we start with the minimum boundary point, if we can identify a possible pouring opportunity, we will be guarranteed to have that much water saved, due to the higher walls on the boundary.
*/
class Cell {
public:
    int x;
    int y;
    int height;
        
    Cell(int _x = 0, int _y = 0, int _height = 0) : x(_x), y(_y), height(_height) {}
    
    bool operator < (const Cell &c) const {
        return height > c.height;
    }
};

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int water = 0;
        if (heightMap.empty() || heightMap[0].empty()) return water;
        int m = heightMap.size(), n = heightMap[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        priority_queue<Cell> pq;
        
        // push all boundary cells into pq to find the way to pour water in
        for (int i = 0; i < m; i++) {
            pq.push(Cell(i, 0, heightMap[i][0]));
            visited[i][0] = true;
            pq.push(Cell(i, n-1, heightMap[i][n-1]));
            visited[i][n-1] = true;
        }
        for (int j = 0; j < n; j++) {
            pq.push(Cell(0, j, heightMap[0][j]));
            visited[0][j] = true;
            pq.push(Cell(m-1, j, heightMap[m-1][j]));
            visited[m-1][j] = true;
        }
        // BFS mininum height way in to pour water
        while (!pq.empty()) {
            Cell cur = pq.top();
            pq.pop();
            for (int i = 0; i < 4; i++) {
                Cell nb(cur.x+dx[i], cur.y+dy[i]);
                if (!inBound(heightMap, nb) || visited[nb.x][nb.y]) continue;
                // pour water into lower cell neighbors if possible
                water += max(0, cur.height-heightMap[nb.x][nb.y]);
                // pass the current max height along
                nb.height = max(heightMap[nb.x][nb.y], cur.height);
                pq.push(nb);
                visited[nb.x][nb.y] = true;
            }
        }
        return water;
        
    }
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>>& heightMap, Cell &c) {
        return c.x >= 0 && c.x < heightMap.size() && c.y >= 0 && c.y < heightMap[0].size();
    }
};
