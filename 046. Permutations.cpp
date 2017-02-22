/*
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
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
