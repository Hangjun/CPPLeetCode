/*
Given an integer n, generate a square matrix filled with elements from 1 to n^2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n));
        if (n == 0) return res;
        int u = 0, d = n-1, l = 0, r = n-1;
        int num = 1;
        while (true) {
            // up
            for (int col = l; col <= r; col++) res[u][col] = num++;
            if (++u > d) break;
            
            // right
            for (int row = u; row <= d; row++) res[row][r] = num++;
            if (--r < l) break;
            
            // down
            for (int col = r; col >= l; col--) res[d][col] = num++;
            if (--d < u) break;
            
            // left
            for (int row = d; row >= u; row--) res[row][l] = num++;
            if (++l > r) break;
        }
        
        return res;
    }
};
