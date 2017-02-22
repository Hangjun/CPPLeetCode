/*
Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7, 
A solution set is: 
[
  [7],
  [2, 2, 3]
]
*/

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
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
            dfs(candidates, i, target-candidates[i], curSoln, res);
            curSoln.pop_back();
        }
    }  
};
