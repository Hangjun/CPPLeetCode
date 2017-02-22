/*
 Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

// Backtracking solution:
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        if (n == 0 || k == 0) return res;
        vector<int> curSoln;
        combineDFS(1, n, k, curSoln, res);
        return res;
    }
    
    void combineDFS(int start, int n, const int k, vector<int> &curSoln, vector<vector<int>> &res) {
        // terminating condition
        if (curSoln.size() == k) {
            res.push_back(curSoln);
            return;
        }
        
        for (int i = start; i <= n; i++) {
            curSoln.push_back(i);
            combineDFS(i+1, n, k, curSoln, res);
            curSoln.pop_back();
        }
    }
};

// Iterative solution:
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        if (n == 0 || k == 0) return res;
        int i = 0;
        vector<int> curSoln(k, 0);
        while (i >= 0) {
            curSoln[i]++;
            if (curSoln[i] > n) {
                --i;
            } else if (i == k-1) {
                res.push_back(curSoln);
            } else {
                ++i;
                curSoln[i] = curSoln[i-1];
            }
        }
        
        return res;
    }
};
