/*
There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

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

Output: 12
Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
             The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.

Example 2

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: -1
Explanation: There is no way for the ball to stop at the destination.

Note:
There is only one ball and one destination in the maze.
Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
*/

/*
Analysis: Based on the idea of part I of this problem, we view this as a short path problem in a graph. Therefore, Dijkstra's algorithm is very natural to use. 

We also like to point out that this problem is essentially the same as Problem 127. Word Ladder (https://leetcode.com/problems/word-ladder/#/description). In the word ladder problem, we manually controlled the distance via BFS.
*/
class Node {
public:
    int x;
    int y;
    int dist;
    
    Node(int _x = 0, int _y = 0, int _dist = 0) : x(_x), y(_y), dist(_dist) {}
    
    bool operator < (const Node &n) const {
        return dist > n.dist;
    }
};

class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return -1;
        int m = maze.size(), n = maze[0].size();
        // visited[i][j] = minimum distance from start to (i, j)
        vector<vector<int>> visited(m, vector<int>(n, INT_MAX));
        priority_queue<Node> pq; // minimum heap
        pq.push(Node(start[0], start[1], 0));
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            Node curNode = pq.top();
            pq.pop();
            if (curNode.x == destination[0] && curNode.y == destination[1]) return curNode.dist;
            // get neighboring stoppping nodes (when we hit the wall)
            for (int i = 0; i < 4; i++) {
                int nx = curNode.x, ny = curNode.y;
                while (inBound(maze, nx+dx[i], ny+dy[i]) && maze[nx+dx[i]][ny+dy[i]] == 0) { 
                    nx += dx[i]; ny += dy[i];
                }
                // now (nx, ny) is a valid "dead node" - we hit a wall
                int curDist = curNode.dist + abs(nx - curNode.x) + abs(ny - curNode.y);
                if (visited[nx][ny] > curDist) {
                    visited[nx][ny] = curDist;
                    pq.push(Node(nx, ny, curDist));
                }
            }
        }
        
        return -1;
    }
    
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &maze, int x, int y) {
        return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size();
    }
};
