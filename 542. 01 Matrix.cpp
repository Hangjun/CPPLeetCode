/*
Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.
Example 1: 
Input:

0 0 0
0 1 0
0 0 0
Output:
0 0 0
0 1 0
0 0 0
Example 2: 
Input:

0 0 0
0 1 0
1 1 1
Output:
0 0 0
0 1 0
1 2 1
Note:
The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.
*/

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return vector<vector<int>>{};
        int m = matrix.size(), n = matrix[0].size();
        queue<pair<int, int>> q;
        // matrix[i][j] need to store the shortest distance to a nearby '0'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j]) matrix[i][j] = INT_MAX;
                else q.push(make_pair(i, j));
            }
        }
                
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (!inBound(matrix, nx, ny) || matrix[nx][ny] <= matrix[x][y] + 1) continue;
                matrix[nx][ny] = matrix[x][y] + 1; // matrix[nx][ny] stores the optmial (shortest distance) value now
                q.push(make_pair(nx, ny));
            }
        }
        return matrix;
    }
    
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>> &matrix, int x, int y) {
        return x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size();
    }
};
