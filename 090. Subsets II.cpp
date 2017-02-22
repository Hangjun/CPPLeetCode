/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

/*
The part I of this problem admists 3 different solutions. All of them can be modified for this problem. We only present the modified backtracking soultion.
*/

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> powerset;
        vector<int> curSoln;
        powerset.push_back(curSoln);
        sort(nums.begin(), nums.end());
        dfs(nums, 0, curSoln, powerset);
        return powerset;
    }
    
    void dfs(vector<int> &nums, int start, vector<int> &curSoln, vector<vector<int>> &powerset) {
        if (start >= nums.size()) return;
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i-1]) continue;
            curSoln.push_back(nums[i]);
            powerset.push_back(curSoln);
            dfs(nums, i+1, curSoln, powerset);
            curSoln.pop_back();
        }
    }
};
