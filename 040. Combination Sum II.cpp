/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
*/

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
        if (candidates.empty()) return res;
        vector<int> curSoln;
        sort(candidates.begin(), candidates.end()); // when in backtracking, sort first
        dfs(candidates, 0, target, curSoln, res);
        
        return res;
    }
    
    void dfs(vector<int> &candidates, int start, int target, vector<int> &curSoln, vector<vector<int>> &res) {
        if (target == 0) {
            res.push_back(curSoln);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // avoid duplicate combination sums
            if (i > start && candidates[i] == candidates[i-1]) continue;
            // avoid infinite loops
            if (candidates[i] > target) continue;
            curSoln.push_back(candidates[i]);
            dfs(candidates, i+1, target-candidates[i], curSoln, res);
            curSoln.pop_back();
        }
    }
};
