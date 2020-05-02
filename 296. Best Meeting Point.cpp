/*
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three people living at (0,0), (0,4), and (2,2):

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.
*/

/*
Analysis: This is really a computational geometry problem. The key is to note that the best meeting point with respect to the 
Manhattan Distance is exactly the median point whose x coordinate is the median of the x coordinates of all the people, and y 
coordinate the median of the y coordinates of all the people. This idea is also used in solving LintCode Post Office Problem. 
This problem is the k = 1 case of the post office problem.
*/

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        vector<int> xCoord;
        vector<int> yCoord;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    xCoord.push_back(i);
                    yCoord.push_back(j);
                }
            }
        }
        
        int n = xCoord.size();
        if (n < 2) return 0;
        sort(xCoord.begin(), xCoord.end());
        sort(yCoord.begin(), yCoord.end());
        int x_median = xCoord[n/2], y_median = yCoord[n/2];
        int dist = 0;
        for (int i = 0; i < n; i++) {
            dist += abs(xCoord[i] - x_median);
            dist += abs(yCoord[i] - y_median);
        }
        
        return dist;
    }
};

