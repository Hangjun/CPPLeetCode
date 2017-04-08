/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty()) return res;
        vector<int> localSoln;
        vector<bool> canUse(nums.size(), true);
        sort(nums.begin(), nums.end()); // When in backtracking, SORT!!!
        dfs(nums, canUse, localSoln, res);
        return res;
    }
    
    void dfs(vector<int> &nums, vector<bool> &canUse, vector<int> &localSoln, vector<vector<int>> &res) {
        if (localSoln.size() == nums.size()) {
            res.push_back(localSoln);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if ((i > 0 && nums[i] == nums[i-1] && canUse[i-1]) || !canUse[i]) continue;
            canUse[i] = false;
            localSoln.push_back(nums[i]);
            dfs(nums, canUse, localSoln, res);
            localSoln.pop_back();
            canUse[i] = true;
        }
    }
};
