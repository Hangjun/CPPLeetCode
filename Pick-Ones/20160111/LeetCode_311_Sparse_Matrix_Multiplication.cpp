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

// Submission #1: Serializing A. Accepted.

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size();
        int n = A[0].size();
        int k = B[0].size();
        vector<vector<int>> res(m, vector<int>(k, 0));
        
        // serialize non-zeros elems of A
        vector<pair<int, int>> AReduce;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j]) {
                    AReduce.push_back(make_pair(i, j));
                }
            }
        }
        
        // given (i, j) in AReduce, need to find all nonzeros elems along
        // row j
        unordered_map<int, vector<int>> BReduce;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (B[i][j]) {
                    BReduce[i].push_back(j);
                }
            }
        }
        
        // multiply AReduce with BReduce
        for (int i = 0; i < AReduce.size(); i++) {
            int x1 = AReduce[i].first;
            int y1 = AReduce[i].second;
            int val1 = A[x1][y1];
            // scan row y1 in BReduce
            int x2 = y1;
            for (int j = 0; j < BReduce[x2].size(); j++) {
                int y2 = BReduce[x2][j];
                int val2 = B[x2][y2];
                res[x1][y2] += val1 * val2;
            }
        }
        
        return res;
    }
};

// submission #2: Binary search optimization when one of the input array is large
