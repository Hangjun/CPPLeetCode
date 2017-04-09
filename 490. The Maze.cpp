/*
There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

Example 1

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

Example 2

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: false
Explanation: There is no way for the ball to stop at the destination.

Note:
There is only one ball and one destination in the maze.
Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
*/

/*
DFS is the straightforward solution. There is one catch about how the stopping condition. Whenever we hit a wall in any direction, we view it as having reached a destination. If that destination equals to the destination required, we return true. Otherwise we can resume from where we hit the wall.
*/
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return false;
        int m = maze.size(), n = maze[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        return dfs(maze, start, destination, visited);
    }
    
    bool dfs(vector<vector<int>> &maze, vector<int> &start, vector<int> &destination, vector<vector<bool>> &visited) {
        if (start[0] == destination[0] && start[1] == destination[1]) return true;
        int x = start[0], y = start[1];
        if (visited[x][y]) return false;
        
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x, ny = y;
            while(inBound(maze, nx + dx[i], ny + dy[i]) && maze[nx+dx[i]][ny+dy[i]] == 0) {
                nx += dx[i]; ny += dy[i];
            }
            vector<int> res = {nx, ny};
            if(dfs(maze, res, destination, visited)) return true;
        }
        return false;
    }
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &maze, int x, int y) {
        return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size();
    }
};
