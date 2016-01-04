/*
Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
*/

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size();
        int n = A[0].size();
        int k = B[0].size();
        vector<vector<int>> res(m, vector<int>(k, 0));
        // store coordinates of non-zero entries of A into A1
        vector<pair<int, int>> A1;
        // store row index-->col index for non-zero entries of B into B1
        unordered_map<int, vector<int>> B1;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j]) {
                    A1.push_back(make_pair(i, j));
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (B[i][j]) {
                    B1[i].push_back(j);
                }
            }
        }
        
        for (int i = 0; i < A1.size(); i++) {
            int xA = A1[i].first;
            int yA = A1[i].second;
            int valA = A[xA][yA];
            // search for non-zero entries in B with row index y1
            int xB = yA;
            vector<int> v = B1[xB];
            for (int j = 0; j < v.size(); j++) {
                int yB = v[j];
                int valB = B[xB][yB];
                res[xA][yB] += valA * valB;
            }
        }
        
        return res;
    }
};
