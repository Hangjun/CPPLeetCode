/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
*/

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> curSoln;
        dfs(1, k, n, curSoln, res);
        return res;
    }
    
    void dfs(int start, int k, int n, vector<int> &curSoln, vector<vector<int>> &res) {
        if (curSoln.size() == k) {
            if (n == 0) res.push_back(curSoln);
            return;
        }
        
        for (int i = start; i <= 9; i++) {
            if (i > n) continue;
            curSoln.push_back(i);
            dfs(i+1, k, n-i, curSoln, res);
            curSoln.pop_back();
        }
    }
};

/*
Remark: Compare with Problem 39 and 40.
*/
