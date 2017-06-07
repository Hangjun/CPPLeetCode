/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res(m * n);
        int u = 0, d = m-1, l = 0, r = n-1;
        int k = 0;
        while (true) {
            // up
            for (int col = l; col <= r; col++) res[k++] = matrix[u][col];
            if (++u > d) break;
            
            // right
            for (int row = u; row <= d; row++) res[k++] = matrix[row][r];
            if (--r < l) break;
            
            // down
            for (int col = r; col >= l; col--) res[k++] = matrix[d][col];
            if (--d < u) break;
            
            // left
            for (int row = d; row >= u; row--) res[k++] = matrix[row][l];
            if (++l > r) break;
        }
        
        return res;
    }
};
