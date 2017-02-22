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
        vector<int> curSoln;
        vector<bool> canUse(nums.size(), true);
        sort(nums.begin(), nums.end());
        permuteDFS(nums, 0, canUse, curSoln, res);
        return res;
    }
    
    void permuteDFS(vector<int> &nums, int start, vector<bool> &canUse, vector<int> &curSoln, vector<vector<int>> &res) {
        if (start == nums.size()) {
            res.push_back(curSoln);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1] && canUse[i-1]) continue;
            if (canUse[i] == true) {
                canUse[i] = false;
                curSoln.push_back(nums[i]);
                permuteDFS(nums, start+1, canUse, curSoln, res);
                canUse[i] = true;
                curSoln.pop_back();
            }
        }
    }
};
